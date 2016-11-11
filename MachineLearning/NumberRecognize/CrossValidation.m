function [Xbayes,Xls,Xsvm] = CrossValidation(dataset, datalabel,threshold, lambda, sigma_C)
n = size(dataset,1);
n = n - mod(n,5);
id = zeros(5,n/5);
%ÐòºÅ
for i = 1:5
    id(i,:) = (n/5)*(i-1)+1:(n/5)*i;
end
Xbayes = zeros(size(threshold,1),5);
Xls = zeros(size(lambda,1),5);
Xsvm = zeros(size(sigma_C,1),5);
for i = 1:5
   testdata = dataset((n/5)*(i-1)+1:(n/5)*i,:);
   testlabel = datalabel((n/5)*(i-1)+1:(n/5)*i);
   traindata = [];
   trainlabel = [];
   for j = 1:5
       if i~=j
           traindata = [traindata;dataset((n/5)*(j-1)+1:(n/5)*j,:)];
           trainlabel = [trainlabel;datalabel((n/5)*(j-1)+1:(n/5)*j)];
       end
   end
   for k = 1:size(threshold,1)
      [~,Xbayes(k,i)] = nbayesclassifier(traindata,trainlabel,testdata,testlabel,threshold(k));
   end
   
   for k = 1:size(lambda,1)
      [~,Xls(k,i)] = lsclassifier(traindata,trainlabel,testdata,testlabel,lambda(k));
   end
   
   for k = 1:size(sigma_C,1)
      [~,Xsvm(k,i)] = softsvm(traindata,trainlabel,testdata,testlabel,sigma_C(k,1),sigma_C(k,2));
   end

end