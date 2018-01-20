clc;

OCVRoot = 'C:\Users\guanc\Downloads\opencv\build';
IPath = ['-I',fullfile(OCVRoot,'include')];
LPath = fullfile(OCVRoot, 'x64\vc14\lib');
lib1 = fullfile(LPath,'opencv_world340.lib');
lib2 = fullfile(LPath,'cxcore210d.lib');

%mex('displayImage.cpp', IPath, lib1);
mex('encodeImageOCV_Changjie.cpp', IPath, lib1);%_SECURE_SCL=1

%%

clc; clear a

OCVRoot = 'C:\Users\guanc\Downloads\opencv\build';
IPath = ['-I',fullfile(OCVRoot,'include')];
LPath = fullfile(OCVRoot, 'x64\vc14\lib');
lib1 = fullfile(LPath,'opencv_world340.lib');
lib2 = fullfile(LPath,'cxcore210d.lib');

%mex('displayImage.cpp', IPath, lib1);
mex('class_interface_mex.cpp', IPath, lib1);%_SECURE_SCL=1

%%

displayImage()

%%

tmp =imread('CAPTURE2.JPEG');
tmp3 = permute(tmp(:,:,[3 2 1]), [3,2,1]);

a = class_interface(3456);
init(a, 960, 1280)
wait(a)
sendImg(a, tmp3)
%%

encodeImageOCV_Changjie(tmp3);


for i =1:5    
    tic
    tmp3 = permute(tmp(:,:,[3 2 1]), [3,2,1]);
    toc
end

encodeImageOCV_Changjie(tmp3);
