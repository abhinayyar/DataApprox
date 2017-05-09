# DataApprox

compile 

g++ -o backprop backprop.cpp

run
./backprop <Data_file_Name> <Learning_Rate> <Max_iterations> <Hidden_Layers>

<Data_File_Name> : imput data which will be used for training and testing data ( Normally considers values for all features)
<Learning_Rate> : Need to tune this to get better rate , normally 0.05 is good rate, but need to tune, bad learning rate can lead to problem of overfitting
<Max_iterations > : Backprop will stop on two conditions, 1: Error rate is too less, below threshold, 2: Max iterations is reached, you can set some high value for this , normally will take time for really high values (10,000)
<Hidden_Layers> : This is property for backprop algorithm, more hidden layer, more chance of fine tune learning, but upto ceratain limit. In this case 5 hidden layers were performing good

Example:
./backprop bthree_attr 0.5 100000 5

Analyze data

There is seprate analyze.cpp file, which can be used to identify type of data patterns

compile cpp file
run
./object_file <data_file_name>

Patterns types
All zero
Lower words (lower bits zero)
Repetion in pattern
Similar patterns
No patterns
