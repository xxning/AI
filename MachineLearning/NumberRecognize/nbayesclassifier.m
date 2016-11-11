function [ypred,accuracy] = nbayesclassifier(traindata,trainlabel, testdata, testlabel, threshold);
traindata=traindata>0;
CYY = traindata' * trainlabel;
CYN = traindata' * (1 - trainlabel);
CNY = (1 - traindata') * trainlabel;
CNN = (1 - traindata') * (1 - trainlabel);
CY = sum(trainlabel);  %正例数目
CN = sum(1 - trainlabel);%反例数目
N = CY+CN; %样例数目

PY = CY/N; %正例概率
PN = CN/N; %反例概率
PYY = CYY/CY; %正例的情况下，像素点为黑的概率
PYN = CYN/CN; %反例的情况下，像素点为黑的概率
PNY = CNY/CY; %正例的情况下，像素点为白的概率
PNN = CNN/CN; %反例的情况下，像素点为白的概率

size_data = size(testdata);
M = size_data(1); %第一维大小
K = size_data(2); %第二维大小

testdata=testdata>0;
PY_test = PY*prod((testdata.*(ones(M,1)*PYY') + (1-testdata).*(ones(M,1)*PNY'))')';
PN_test = PN*prod((testdata.*(ones(M,1)*PYN') + (1-testdata).*(ones(M,1)*PNN'))')';
P_test = PY_test./(PY_test+PN_test);
ypred = P_test>threshold;
%ypred = PY_test>PN_test;
accuracy = sum(ypred==testlabel)/M;
