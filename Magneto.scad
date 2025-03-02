/* [Paramters] */
$fn=50;
bodThick = 5;
desHtRad = 20;

/* [Hidden] */
inch = 25.4;
//
/* [Wheels] */
//
module wheel(){
    difference(){
        union(){
            scale([s,s,s])import("1_10_tyre.stl");
            translate([desHt/2-0.25,0.1,desHt/2-0.25])rotate([-90,0,0])cylinder(r=4.5,h=7);
        }
        translate([desHt/2-0.25,3,desHt/2-0.25])cube([3.5,6.1,5.5],center=true);
    }
}
//
module wheelM(){
    difference(){
        union(){
            scale([s,s,s])import("1_10_tyre_mirrored.stl");
            translate([desHt/2-0.25,0.1,desHt/2-0.25])rotate([-90,0,0])cylinder(r=4.5,h=7);
        }
        translate([desHt/2-0.25,3,desHt/2-0.25])cube([3.5,6.1,5.5],center=true);
    }
}
//

initHt = 70;
initDepth = 30;
desHt = desHtRad*2;
s = desHt/initHt;
motorWidth = 20;
motorDiam = 28;
breadBoardWidth = 56.5;
breadBoardLength = 86.5;
boxThick = 2.5;
boxHt = motorDiam/2;
bodWidth = 55+2*boxThick;
bodLength = 4/3*(breadBoardLength+motorDiam+breadBoardWidth/2)+2*boxThick;
//
module carBox(){
    difference(){
        cube([breadBoardLength+2*boxThick,breadBoardWidth+2*boxThick,boxHt]);
        translate([boxThick,boxThick,-.1]) cube([breadBoardLength,breadBoardWidth,boxHt+.2]);
    }
}
//
//carBox();
//

// motor grab is 2.5 mm x 4.5 mm (add 1 mm leeway)

module wheels(){
    translate([0,bodWidth*0.5,0]) wheel();
    translate([0,-bodWidth*0.5,0]) translate([desHt,0,0])rotate([0,0,180]) wheelM();
}
//
//wheels();
module carBall(){
    translate([bodLength*3/4,0,desHt/2])sphere(d=bodWidth*0.5);
}
//
module carBody(){
    difference(){
        union(){
            translate([bodLength*3/8,0,desHt/2])cube([bodLength*3/4,bodWidth,bodThick],center=true);
            translate([bodLength*3/4,0,desHt/2])cylinder(d=bodWidth,h=bodThick,center=true);
        }
         translate([bodLength*3/4,0,0])cylinder(d=bodWidth*.5*1.05,h=desHt);
    }
}
//
//carBody();
//carBall();
module ballCap(){
    difference(){
        translate([bodLength*3/4,0,desHt/2])
        difference(){
            sphere(d=bodWidth*.5*1.5);
            rotate([180,0,0])cylinder(d=bodWidth*.5*1.5*1.1,h=bodWidth*.5*1.5*1.1);
        }
        translate([bodLength*3/4,0,desHt/2])scale([1.05,1.05,1.05])sphere(d=bodWidth*0.5);
    }
}
//
//ballCap();
//
module motorCup(){
    translate([0,-motorWidth/2,0])difference(){
        cube([motorDiam,motorWidth,motorDiam*5/8]);
        translate([motorDiam/2,-.1,motorDiam*5/8])rotate([-90,0,0])cylinder(d=motorDiam,h=motorWidth+.2);
        translate([-.1,-.1,motorDiam*5/8-6.5])cube([motorDiam+.2,motorWidth+.2,10]);
    }
}
//
//motorCup();
//
module fullCarBody(){
    carBody();
    ballCap();
    translate([0,bodWidth/2-motorWidth/2,desHt/2+bodThick/2])motorCup();
    translate([0,-bodWidth/2+motorWidth/2,desHt/2+bodThick/2])motorCup();
    translate([motorDiam+boxThick,-bodWidth/2,desHt/2])carBox();
}
//
//fullCarBody();
//wheels();
//

/* [Helmet] */
fullHelmHt = 317.94;
fullHelmDepth = 244.72;
fullHelmWidth = 207.89;
//
module helm(){
    import("whole_helmet.stl");
}
//
module helmBotRight(){
    import("bottom_right.stl");
}
//
module helmTopRight(){
    import("top_left.stl");
}
//
module helmBotLeft(){
    import("bottom_left.stl");
}
//
module helmTopLeft(){
    import("top_left.stl");
}
//
//helm();
//helmBotRight();
//helmTopRight();
//helmBotLeft();
//helmTopLeft();

module frontHelm(){
    difference(){
        helm();
        translate([0,-fullHelmHt*0.125,-fullHelmDepth/4-.1])cube([fullHelmWidth+.2,fullHelmHt,fullHelmDepth/2+.1],center=true);
    }
}
//
//frontHelm();
//

yLen = fullHelmHt*5/8;
module helmBlockLeft(){
    difference(){
        translate([-fullHelmWidth/2,-33-yLen,-.1])cube([fullHelmWidth*0.4,yLen,fullHelmDepth*1/2]);
        translate([0,0,-0.1+fullHelmDepth*1/4])rotate([0,0,-45])cube([100,125,fullHelmDepth*1/2+0.2],center=true);
    }
}
//
module helmBlockRight(){
    difference(){
        translate([fullHelmWidth/2-fullHelmWidth*0.4,-33-yLen,-.1])cube([fullHelmWidth*0.4,yLen,fullHelmDepth*1/2]);
        translate([0,0,-0.1+fullHelmDepth*1/4])rotate([0,0,45])cube([100,125,fullHelmDepth*1/2+0.2],center=true);
    }
}
//
//helmBlockRight();
//helmBlockLeft();
//
module frontHelmTop(){
    difference(){
        frontHelm();
        helmBlockRight();
        helmBlockLeft();
    }
}
//
module frontHelmRight(){
    intersection(){
        frontHelm();
        helmBlockRight();
    }
}
//
module frontHelmLeft(){
    intersection(){
        frontHelm();
        helmBlockLeft();
    }
}
//
//frontHelmTop();
//frontHelmRight();
//frontHelmLeft();
desHelmHt = 300;
desHelmDepth = fullHelmDepth;
desHelmWidth = 200;
//helm();
helmTopSplit = fullHelmDepth*3/8;
module frontHelmTopBot(){
    difference(){
        frontHelmTop();
        translate([0,0,50+helmTopSplit])cube([fullHelmWidth*9/8,fullHelmHt,100],center=true);
    }
}
//
module frontHelmTopTop(){
    intersection(){
        frontHelmTop();
        translate([0,0,50+helmTopSplit])cube([fullHelmWidth*9/8,fullHelmHt,100],center=true);
    }
}
//
////frontHelmTopBot();
//difference(){
//    frontHelmTopTop();
//    translate([0,-fullHelmHt/2,-.1])cube(fullHelmHt);
//}
//
//intersection(){
//    frontHelmTopTop();
//    translate([0,-fullHelmHt/2,-.1])cube(fullHelmHt);
//}
//

