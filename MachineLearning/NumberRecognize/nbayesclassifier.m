function [ypred,accuracy] = nbayesclassifier(traindata,trainlabel, testdata, testlabel, threshold);
traindata=traindata>0;
CYY = traindata' * trainlabel;
CYN = traindata' * (1 - trainlabel);
CNY = (1 - traindata') * trainlabel;
CNN = (1 - traindata') * (1 - trainlabel);
CY = sum(trainlabel);  %������Ŀ
CN = sum(1 - trainlabel);%������Ŀ
N = CY+CN; %������Ŀ

PY = CY/N; %��������
PN = CN/N; %��������
PYY = CYY/CY; %����������£����ص�Ϊ�ڵĸ���
PYN = CYN/CN; %����������£����ص�Ϊ�ڵĸ���
PNY = CNY/CY; %����������£����ص�Ϊ�׵ĸ���
PNN = CNN/CN; %����������£����ص�Ϊ�׵ĸ���

size_data = size(testdata);
M = size_data(1); %��һά��С
K = size_data(2); %�ڶ�ά��С

testdata=testdata>0;
PY_test = PY*prod((testdata.*(ones(M,1)*PYY') + (1-testdata).*(ones(M,1)*PNY'))')';
PN_test = PN*prod((testdata.*(ones(M,1)*PYN') + (1-testdata).*(ones(M,1)*PNN'))')';
P_test = PY_test./(PY_test+PN_test);
ypred = P_test>threshold;
%ypred = PY_test>PN_test;
accuracy = sum(ypred==testlabel)/M;
