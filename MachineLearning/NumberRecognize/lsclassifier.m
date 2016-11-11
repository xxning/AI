function [ypred,accuracy] = lsclassifier(traindata, trainlabel, testdata, testlabel, lambda)
[m,n] = size(traindata);
global data;
data=ones(m,n+1);
%for i=1:1:m
%    data(i,1)=1;
%end
for i=1:1:m
    for j=2:1:n+1
        data(i,j)=traindata(i,j-1);
    end
end

w = inv((data' * data + lambda * eye(n+1))')* data'*trainlabel;
[m,n] = size(testdata);
data=ones(m,n+1);
%for i=1:1:m
%    data(i,1)=1;
%end
for i=1:1:m
    for j=2:1:n+1
        data(i,j)=testdata(i,j-1);
    end
end

ypred = (data * w) >= 0.5;
accuracy = sum(ypred==testlabel)/m;
