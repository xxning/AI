function [ypred,accuracy] = softsvm(traindata, trainlabel,testdata, testlabel , sigma, C)
trainY = trainlabel * 2 - 1; %0->-1;1->1
[m,n] = size(traindata);
[m2,~] = size(testdata);    
%核函数处理
if (sigma == 0)
    K = traindata * traindata';
else
    K=traindata*traindata'/sigma^2;
    d=diag(K);
    K=2*K;
    K=K-ones(m,1)*d';
    K=K-d*ones(1,m);
    K=exp(K);
end
%求解alpha
H = K .* (trainY * trainY');
f = -ones(m,1);
Aeq=trainY';
beq=0;
lb=zeros(m,1);
ub=zeros(m,1)+C;
alpha = quadprog(H, f,[],[], Aeq, beq, lb, ub);
%求b
bv = (trainY-K*(alpha.*trainY)).*(alpha~=0);
b = sum(bv) / sum(alpha~=0);
%测试数据
if sigma == 0
    K = traindata * testdata';
else
    Delta = reshape(repmat(traindata,1,m2) - repmat(reshape(testdata',1,m2*n),m,1),m,n,m2);
    SquareSum = reshape(sum(Delta.^2,2),m,m2);
    SquareSum = -SquareSum/(sigma^2);
    K = exp(SquareSum);
end
ypred = (((alpha.*trainY)'*K+b)>0)';
accuracy = sum(ypred==testlabel)/m2;