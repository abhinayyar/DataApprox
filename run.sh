echo "GAUSIAN >>. " >> rod_lthree_attr_out

echo "0.01 Learning rate , 1000 Iterations " >> rod_lthree_attr_out
./bp lthree_attr 0.01 1000 >> rod_lthree_attr_out
echo "0.01 Learning rate , 10000 Iterations " >> rod_lthree_attr_out
./bp lthree_attr 0.01 10000 >> rod_lthree_attr_out
echo "0.01 Learning rate , 100000 Iterations " >> rod_lthree_attr_out
./bp lthree_attr 0.01 100000 >> rod_lthree_attr_out
echo "0.001 Learning rate , 1000 Iterations " >> rod_lthree_attr_out
./bp lthree_attr 0.001 1000 >> rod_lthree_attr_out
echo "0.001 Learning rate , 10000 Iterations " >> rod_lthree_attr_out
./bp lthree_attr 0.001 10000 >> rod_lthree_attr_out
echo "0.001 Learning rate , 100000 Iterations " >> rod_lthree_attr_out
./bp lthree_attr 0.001 100000 >> rod_lthree_attr_out
echo "-------------------------" >> rod_lthree_attr_out
