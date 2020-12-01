thickness = 4;
rodDiameter = 4;
cleatLength = 10;
bearingDepth = 4;
bearingDiameter = 10;
screwHeadDiameter = 8;
screwDiameter = 3;
bearingSprocketDiameter = 5.9;
servoScrewDiameter = 2.9+0.4;
servoHornLength = 37.8;
servoHornScrewDiameter = 6.5;
servoHornScrewOffset = 14.7/2;
servoHornScrewSpacing = 3;
setScrewDiameter = 2.5;

style = 3;

setScrewRadius = setScrewDiameter/2;
bearingSprocketRadius = bearingSprocketDiameter/2;
servoScrewRadius = servoScrewDiameter/2;
screwRadius = screwDiameter/2;
bearingRadius = bearingDiameter/2;
screwHeadRadius = screwHeadDiameter/2;
rodRadius = rodDiameter/2;
bodyWidth = thickness*4 + rodDiameter;
bodyLength = cleatLength+thickness*2;
bodyDepth = (thickness+rodRadius);
rodHolderRadius = thickness+rodRadius;
servoSprocketDepth = 4;
servoHornScrewRadius = servoHornScrewDiameter/2;

$fn = 36;

// Base and rod holders
baseAndRodHolder();
module baseAndRodHolder(){
    difference(){
        translate([0,0,(bodyDepth)/2]){
            cube([bodyWidth, bodyLength, bodyDepth], center = true);
            translate([bodyWidth/2,0,rodHolderRadius/2]){
                rotate([90,0,0]){
                    cylinder(bodyLength, rodHolderRadius, rodHolderRadius, center=true);
                }
            }
            translate([-bodyWidth/2,0,rodHolderRadius/2]){
                rotate([90,0,0]){
                    cylinder(bodyLength, rodHolderRadius, rodHolderRadius, center=true);
                }
            }
            translate([0,0,rodHolderRadius/2]){
                rotate([90,0,90]){
                    cylinder(bodyWidth+rodHolderRadius*2, rodHolderRadius, rodHolderRadius, center=true);
                }
            }
        }
        translate([bodyWidth/2,-thickness,rodHolderRadius]){
            rotate([90,0,0]){
                if(style == 3){
                    cylinder(bodyLength*2, rodRadius, rodRadius, center=true);
                }else{
                    cylinder(bodyLength*1, rodRadius, rodRadius, center=true);
                }
            }
        }
        translate([-bodyWidth/2,-thickness,rodHolderRadius]){
            rotate([90,0,0]){
                if(style == 3){
                    cylinder(bodyLength*2, rodRadius, rodRadius, center=true);
                }else{
                    cylinder(bodyLength*1, rodRadius, rodRadius, center=true);
                }
            }
        }
        translate([0,0,rodHolderRadius]){
            rotate([90,0,90]){
                cylinder(bodyLength*2, setScrewRadius, setScrewRadius, center=true);
            }
        }
        translate([0,0,0]){
            rotate([0,0,0]){
                
            }
        }
    }
//    // Cleats
//    translate([bodyWidth/2,0,0]){
//        rotate([0,0,0]){
//            cleat(cleatLength, thickness, 0);
//        }
//    }
//    translate([-bodyWidth/2,0,0]){
//        rotate([0,0,180]){
//            cleat(cleatLength, thickness, 0);
//        }
//    }
}



//Bearing holder
if (style == 0){
    bearingCupHeight = max((bearingDepth+thickness), (rodRadius*2 + thickness*2));
    translate([0,bodyLength/2+bearingRadius,(bearingCupHeight)/2]){
        difference(){
            cylinder(bearingCupHeight, bearingRadius+thickness, bearingRadius+thickness, center = true);
            translate([0,0,(bearingCupHeight-bearingDepth)/2]){
                cylinder(bearingDepth*1.001, bearingRadius, bearingRadius, center = true);
            }
            cylinder((bearingDepth + thickness)*2, screwHeadRadius, screwHeadRadius, center = true);
        }
    }
}

//Bearing mate
if (style == 1){
    translate([0,bodyLength/2+bearingRadius,rodHolderRadius]){
        difference(){
            translate([0,0,0]){
                cylinder(rodHolderRadius*2, bearingRadius+thickness, bearingRadius+thickness, center = true);
                translate([0,0,0.5]){
                    cylinder(rodHolderRadius*2+1, screwHeadRadius, screwHeadRadius, center = true);
                }
            }
            cylinder(rodHolderRadius*5, screwRadius, screwRadius, center = true);
        }
    }
}

// Servo connector
if (style == 2){
    translate([0,bodyLength/2+bearingSprocketRadius,rodHolderRadius]){
        difference(){
            cylinder(rodHolderRadius*2, bearingSprocketRadius+thickness, bearingSprocketRadius+thickness, center = true);
            cylinder(rodHolderRadius*5, servoScrewRadius, servoScrewRadius, center = true);
            translate([0,0,rodHolderRadius-servoSprocketDepth/2+0.001]){
                cylinder(servoSprocketDepth, bearingSprocketRadius, bearingSprocketRadius, center = true);
            }
        }
    }
}

// Servo horn connector
if (style == 3){
    translate([0,bodyLength/2+servoHornScrewRadius,0]){
        difference(){
            translate([0,0,thickness/2]){
                cylinder(thickness, bodyWidth/2+thickness/2+servoHornScrewSpacing*2, bodyWidth/2+thickness/2+servoHornScrewSpacing*2, center = true);
                translate([0,0,rodHolderRadius]){
                    cylinder(rodHolderRadius*2-thickness, bodyWidth/2-rodRadius, bodyWidth/2-rodRadius, center = true);
                }
            }
            cylinder(bodyDepth*5, servoHornScrewRadius, servoHornScrewRadius, center = true);
//            translate([(servoHornScrewOffset),0,thickness/2]){
//                cylinder((thickness)*2, servoScrewRadius, servoScrewRadius, center = true);
//            }
//            translate([-(servoHornScrewOffset),0,thickness/2]){
//                cylinder((thickness)*2, servoScrewRadius, servoScrewRadius, center = true);
//            }
            translate([(servoHornScrewOffset+servoHornScrewRadius*2),0,thickness/2]){
                cylinder((thickness)*2, servoScrewRadius, servoScrewRadius, center = true);
            }
            translate([-(servoHornScrewOffset+servoHornScrewRadius*2),0,thickness/2]){
                cylinder((thickness)*2, servoScrewRadius, servoScrewRadius, center = true);
            }
        }
        translate([0,bodyLength/2+servoHornScrewRadius,0]){
            rotate([0,0,0]){
                baseAndRodHolder();
            }
        }
    }
    
    // Endcap
    translate([bodyWidth/2,-bodyLength/2+thickness/2,rodHolderRadius]){
        rotate([90,0,0]){
            cylinder(thickness, rodHolderRadius, rodHolderRadius, center=true);
        }
    }
    translate([-bodyWidth/2,-bodyLength/2+thickness/2,rodHolderRadius]){
        rotate([90,0,0]){
            cylinder(thickness, rodHolderRadius, rodHolderRadius, center=true);
        }
    }
}

// 24Eng // 24Eng // 24Eng // 24Eng // 24Eng // 24Eng // 24Eng // 24Eng // 24Eng // 24Eng|
// Modules // Modules // Modules // Modules // Modules // Modules // Modules // Modules  |
// 24Eng // 24Eng // 24Eng // 24Eng // 24Eng // 24Eng // 24Eng // 24Eng // 24Eng // 24Eng|
module cleat(funLength, funThickness, funRotation){
    
    rotate([0,0,funRotation]){
        translate([funThickness/2,0,0]){
            difference(){
                cube([funThickness,funLength,funThickness], center=true);
                translate([0,funLength/2,0]){
                    cylinder(funThickness*2, funThickness/2, funThickness/2, center=true);
                }
                translate([0,-funLength/2,0]){
                    cylinder(funThickness*2, funThickness/2, funThickness/2, center=true);
                }
                translate([funThickness/2,0,0]){
                    cylinder(funThickness*2, funThickness/2, funThickness/2, center=true);
                }
            }
        }
        translate([funThickness*1.5,0,0]){
            union(){
                difference(){
                    cube([funThickness,funLength,funThickness], center=true);
                    translate([-funThickness/2,0,0]){
                        cylinder(funThickness*2, funThickness/2, funThickness/2, center=true);
                    }
                }
                translate([0,funLength/2,0]){
                    cylinder(funThickness*1, funThickness/2, funThickness/2, center=true);
                }
                translate([0,-funLength/2,0]){
                    cylinder(funThickness*1, funThickness/2, funThickness/2, center=true);
                }
            }
        }
    }
}