import pandas as pd
import numpy as np
from sklearn.tree import DecisionTreeClassifier
import joblib

# File paths
DATA_FILE = "emg_features.csv"
MODEL_FILE = "emg_model.pkl"
C_CODE_FILE = "model_rules.h"

# Load data
print(f"Loading dataset: {DATA_FILE}")
df = pd.read_csv(DATA_FILE)

# Prepare features (X) and labels (y)
X = df.iloc[:, :-1].values  # All columns except last (features)
y = df.iloc[:, -1].values   # Last column (movement labels)

# Train Decision Tree Classifier
print(" Training Decision Tree Model...")
clf = DecisionTreeClassifier(max_depth=4)  # Small model for ESP32
clf.fit(X, y)

#  Save trained model
joblib.dump(clf, MODEL_FILE)
print(f" Model saved as {MODEL_FILE}")

# Convert model to C-style if-else rules
print(" Converting model to C++ rules for ESP32...")

thresholds = clf.tree_.threshold
features = clf.tree_.feature
children_left = clf.tree_.children_left
children_right = clf.tree_.children_right
values = clf.tree_.value

def generate_if_else(node=0, depth=0):
    """ Recursively convert Decision Tree into C++ if-else rules """
    indent = "    " * depth

    if children_left[node] == -1 and children_right[node] == -1:
        # Leaf node: Return predicted class
        movement = np.argmax(values[node])
        return f"{indent}return {movement}; // Movement: {movement}"

    feature_index = features[node]
    threshold = thresholds[node]

    # Split condition
    condition = f"X[{feature_index}] <= {threshold:.2f}"

    # Recursive branches
    left_branch = generate_if_else(children_left[node], depth + 1)
    right_branch = generate_if_else(children_right[node], depth + 1)

    return f"{indent}if ({condition}) {{\n{left_branch}\n{indent}}} else {{\n{right_branch}\n{indent}}}"

# Generate C++ Code
cpp_code = f"""#ifndef MODEL_RULES_H
#define MODEL_RULES_H

// Decision Tree Model for ESP32
inline int predict_movement(float X[6]) {{
{generate_if_else()}
}}

#endif // MODEL_RULES_H
"""

# Save the generated C++ rules
with open(C_CODE_FILE, "w") as f:
    f.write(cpp_code)

print(f"C++ model saved as {C_CODE_FILE}")
print(" Training complete! Ready to deploy to ESP32.")
