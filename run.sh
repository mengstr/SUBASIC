#cd macrotests/testcasegen
#source build.sh
#cd ../..

../SLEQASM/sleqasm subasic.sleq 0 $1 && ../SLEQASM/subleq  subasic.v20raw $1
