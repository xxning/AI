function[proj_matrix,recons_data,recons_error]=reconsPCA(train_data,test_data, ground_truth,threshold)

[n,d]=size(train_data);
avg=zeros(1,d);
for i=1:1:n
    avg=avg+train_data(i,:);
end
avg=avg/n;

S=zeros(d,d);
for i=1:1:n
    S=S+(train_data(i,:)-avg)'*(train_data(i,:)-avg);
end
S=S/n;

Evalues=eigs(S,100);
[D,~]=eigs(S,100);
Evalues=abs(Evalues);

Sum=sum(Evalues);
sm=0;
m=0;    
for i=1:1:100
    sm=sm+Evalues(i);
    t=sm/Sum;
    if t>=threshold
        m=i;
        break;
    end
end
P=zeros(d,m);
for i=1:1:m
    P(:,i)=D(:,i);
end
proj_matrix=(P'* test_data')';
recons_data=(P*proj_matrix')';
[n,~]=size(test_data);
recons_error=zeros(n,1);
for i=1:1:n
    temp=ground_truth(i,:)-recons_data(i,:);
    temp=temp.*temp;
    recons_error(i)=sum(temp)/2500;
end
    

    
    