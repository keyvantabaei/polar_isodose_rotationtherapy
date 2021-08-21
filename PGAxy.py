import math

angle=360
NoBeam=36
start_angle=0
energy="500 keV"
halfX=5
halfY=3.5
photons=100
angle_between_each_beam=angle/(NoBeam)
SAD=100
Arc_therapy=False

print("/run/initialize")
print("/control/verbose  0")
print("/run/verbose 0")
print("/event/verbose    0")
print("/tracking/verbose 0")
print("/gps/source/intensity 1")

if(Arc_therapy):
    for i in range(NoBeam+1):
        print("############################## Beam ",i+1," ########################")
        if(i==0):theta=start_angle
        elif(i==NoBeam):theta=start_angle+angle
        else:theta=(start_angle+i*angle_between_each_beam)
        theta=(theta*math.pi)/180
        right_angle_rad=(90*math.pi)/180
        if(i!=0):print("/gps/source/add 1")
        print("/gps/particle gamma")
        print("/gps/pos/type Beam")
        print("/gps/ene/type Mono")
        print("/gps/ene/mono ",energy)
        print("/gps/pos/type Plane")
        print("/gps/pos/shape Rectangle")
        print("/gps/pos/rot1 ",round(1*math.cos(right_angle_rad-theta),4),round(-1*math.sin(right_angle_rad-theta),4)," 0 ")
        print("/gps/pos/rot2 0 0 1")
        print("/gps/pos/halfy ",halfY," cm")
        print("/gps/pos/halfx ",halfX," cm")
        X_direct=round(-1*math.cos(theta),4)
        Y_direct=round(-1*math.sin(theta),4)
        print("/gps/pos/centre",-1*SAD*X_direct,-1*SAD*Y_direct," 0 "," cm")
        print("")
        print("/gps/direction",X_direct,Y_direct," 0 ")
        print("############################## END  ########################")
        print("")
    print("/run/beamOn ",photons)
    print("")
    print("# ArcTherapy :",Arc_therapy)
    print("# Therapy Angle :",angle)
    print("# Therapy Plan : ZX")
    print("# Starting angle :",start_angle)
    print("# Number of Beams :",NoBeam+1)
    print("# Angle Between Each Beam :",angle_between_each_beam)
    print("# SAD :",SAD," cm")
    print("# Field Size Y:",2*halfX," X : ",2*halfX," cm")
    print("# Energy :",energy)        
else:
    for i in range(NoBeam):
        print("############################## Beam ",i+1," ########################")
        if(i==0):theta=start_angle
        else:theta=(start_angle+i*angle_between_each_beam)
        theta=(theta*math.pi)/180
        right_angle_rad=(90*math.pi)/180
        if(i!=0):print("/gps/source/add 1")
        print("/gps/particle gamma")
        print("/gps/pos/type Beam")
        print("/gps/ene/type Mono")
        print("/gps/ene/mono ",energy)
        print("/gps/pos/type Plane")
        print("/gps/pos/shape Rectangle")
        print("/gps/pos/rot1 ",round(1*math.cos(right_angle_rad-theta),4),round(-1*math.sin(right_angle_rad-theta),4)," 0 ")
        print("/gps/pos/rot2 0 0 1")
        print("/gps/pos/halfy ",halfY," cm")
        print("/gps/pos/halfx ",halfX," cm")
        X_direct=round(-1*math.cos(theta),4)
        Y_direct=round(-1*math.sin(theta),4)
        print("/gps/pos/centre",-1*SAD*X_direct,-1*SAD*Y_direct," 0 "," cm")
        print("")
        print("/gps/direction",X_direct,Y_direct," 0 ")
        print("############################## END  ########################")
        print("")
    print("/run/beamOn ",photons)
    print("")
    print("# ArcTherapy :",Arc_therapy)
    print("# Therapy Angle :",angle)
    print("# Therapy Plan : ZX")
    print("# Starting angle :",start_angle)
    print("# Number of Beams :",NoBeam)
    print("# Angle Between Each Beam :",angle_between_each_beam)
    print("# SAD :",SAD," cm")
    print("# Field Size Y:",2*halfY," X : ",2*halfX," cm")
    print("# Energy :",energy)

