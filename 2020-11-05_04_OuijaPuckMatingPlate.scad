thickness = 2;
magnetThickness = 5;
magnetDiameter = 12;
puckThickness = 5;
majorRadius = 40;
minorRadius = 50;
viewportRadius = 12;
mountingScrewDiameter = 3;


cylinderOffset = 10;
magnetRadius = magnetDiameter/2;
mountingScrewRadius = mountingScrewDiameter/2;

$fn=60;
difference(){
    translate([0,0,0]){
        cube([viewportRadius*2+magnetRadius*2+thickness*2, magnetRadius*2+thickness*2, puckThickness], center=true);
        translate([(viewportRadius + magnetRadius + thickness),0,0]){
            cylinder(puckThickness, magnetRadius+thickness, magnetRadius+thickness, center=true);
        }
        translate([-(viewportRadius + magnetRadius + thickness),0,0]){
            cylinder(puckThickness, magnetRadius+thickness, magnetRadius+thickness, center=true);
        }
    }
    translate([0,0,0]){
        cylinder(puckThickness*2, mountingScrewRadius, mountingScrewRadius, center=true);
        cylinder(puckThickness*.501, mountingScrewRadius, mountingScrewRadius*3, center=false);
    }
    translate([-(viewportRadius+magnetRadius+thickness),0,puckThickness/2-magnetThickness+0.01]){
        cylinder(magnetThickness, magnetRadius, magnetRadius, center=false);
    }
    translate([(viewportRadius+magnetRadius+thickness),0,puckThickness/2-magnetThickness+0.01]){
        cylinder(magnetThickness, magnetRadius, magnetRadius, center=false);
    }
}