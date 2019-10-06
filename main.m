%Navigation Message file from ftp://cddis.nasa.gov/gnss/data/daily/2019/022/19n/
% https://www.navcen.uscg.gov/?pageName=gpsTechnicalReferences
%File date 22 January 2019

clear all
close all

ant.Pattern = dlmread('data/antenna1.csv');
ant.LBody=[0 0 0];
ant.TransformMatrix=eye(3);

rec.minElev=12;%degree
rec.ant=ant;
%rec.wp=[30 32 900 0 0 0 ];%ReadWPFile('LandVehicle');
rec.moveStartTime=GetDateTime('22-Jan-2019 00:00:00');

sim.ephFile.name='data\ankr022m.19n';%rinex 2.10 //  'log_24h.15n';%rinex 3.03
sim.start=GetDateTime('22-Jan-2019 00:12:00');
sim.end=GetDateTime('22-Jan-2019 00:13:00');

%  sim.ephFile.name='data\ankr027m.18n';%rinex 3.03
%  sim.start=GetDateTime('27-Nov-2018 10:03:00');
%  sim.end=GetDateTime('27-Nov-2018 10:04:00');


[sat.eph, sim.ephFile, sat.navBits, sat.alm]=ReadRinexNMFile(sim.ephFile);
writetable(sat.eph(:,1:31),[sim.ephFile.name '.csv'])

satRec=[];
resSendData=[];

wp_p = [ lla2ecef( [40.0, 32, 816] ) ; lla2ecef( [40,32,816]); ];
wp_v = [0 ; 0];
motionModel = InitMotionModel(wp_p, wp_v);



for t=0:2:seconds(sim.end.dt-sim.start.dt)

    sim.currTime=GetDateTime(sim.start.dt+datenum(0,0,0,0,0,t)) ;
    [rec.pos, rec.llhHR, rec.xyzHR, rec.vxyzHR, motionModel] =RecPosHR(sim.currTime, 2, motionModel);
    sat.pos=SatPosLR(sim.currTime,sat.eph, 2,rec.pos);%Bit Stream burada saniye basina gelmeli
    satRec=CalcLOSViewSV(sim.currTime, sat.pos, rec);
    [satRec.rec.llhHR, satRec.rec.xyzHR, satRec.rec.vxyzHR] = deal(rec.llhHR(1:end-1,:), rec.xyzHR(1:end-1,:), rec.vxyzHR(1:end-1,:));
    satRec=EstSatRecPosHR(satRec);
    [gpsSignalParam, sat.navBits]=CalcGpsSignalParams(sim.currTime, sat, satRec,[1 1 1]);   
    [sendData, resSendData]=SendGpsSignalParams(gpsSignalParam,resSendData);
end
toc

function motionModel = InitMotionModel(wp_p, wp_v)
    %motionModel.wp_p = [3, 2, 0; 72, 72, 0; 0,144,0; 0, 250, 0; -20, 100, 0]*1000/3;
    %motionModel.wp_v = [1000,800,1000,900, 1000]/4;
    motionModel.wp_p = wp_p;
    motionModel.wp_v = wp_v;

    motionModel.a_max_s = 2 * 9.81; %max turn g
    motionModel.a_max_f = 0.4 * 9.81; % max throttle/brake g

    %initial values
    aa=norm((motionModel.wp_p(2,:) - motionModel.wp_p(1,:)));
    if (aa==0)
    motionModel.vel =[0 , 0,0];
    else
    motionModel.vel = motionModel.wp_v(1) * (motionModel.wp_p(2,:) - motionModel.wp_p(1,:)) /aa ;
    end
    motionModel.pos = motionModel.wp_p(1,:);
    motionModel.acc = [0,0,0];

    %set target
    motionModel.targetWP = 2;
    motionModel.target_pos = motionModel.wp_p(motionModel.targetWP,:); %target
    motionModel.target_vel = motionModel.wp_v(motionModel.targetWP); %target 

    motionModel.t = 0;
    motionModel.path_len = 0;
    motionModel.done = 0;
        
end
