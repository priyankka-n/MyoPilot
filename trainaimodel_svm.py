
from sklearn.model_selection import train_test_split
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score

# Load dataset
df = pd.read_csv("emg_training_data.csv")

# Extract features & labels
X = df[["MAV", "RMS", "ZCR"]].values  # Feature matrix with pre-processed values from filter.py code
y = df["Label"].values  # Class labels (movement commands)

# Split into training & testing sets (80% train, 20% test)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Train the SVM classifier
model = SVC(kernel="linear")
model.fit(X_train, y_train)

# Test model performance
y_pred = model.predict(X_test)
accuracy = accuracy_score(y_test, y_pred)
print(f"Model Training Complete!! Accuracy: {accuracy:.2f}")
