#/bin/bash


runSimpleTest() {
    local executable="$1"
    local argument="$2"
    local noexecutable="${1} does not exist!"
    local executablefail="${1} ${2} exited abnormally!"
    local executablesucc="${1} ${2} exited normally"

    if [ ! -e "${executable}.txt" ]
    then
	echo "" > ${executable}.txt
    fi

    echo "Running test ${executable} ${argument}" >> ${executable}.txt
    echo "======================================" >> ${executable}.txt
    if [ -e "$executable" ]
    then
	./${executable} ${argument} &>> ${executable}.txt
	if [ $? -eq 0 ]
	then
	    echo "${executablesucc}"
	else
	    echo "${executablefail}"
	fi
    else
	echo "${noexecutable}"
    fi
    echo "" >> ${executable}.txt
}


###################################################################
############ MAIN CODE ############################################
###################################################################

if [ ! -e "TestDirectory" ]
then
    mkdir TestDirectory
fi
cd TestDirectory

if [ ! -e "CopiedFilesBankAccount" ]
then
    for file in BankAccount.cpp BankAccount.h
    do
	cp ../${file} .
    done

    for file in makefile \
	        TesterBase.cpp TesterBase.h \
	        BankAccountTester.h BankAccountTester.cpp \
                BankAccountMain.cpp
    do
	wget "https://campus.cs.le.ac.uk/teaching/resources/CO7105/Worksheets/assessment2/test/${file}" >& /dev/null
    done

    touch CopiedFilesBankAccount
fi

make BankAccountMain &> BankAccountCompilation.txt


ulimit -SH -c 0            # Maximum size of core files
ulimit -SH -d 4000         # maximum size of process' data segment
ulimit -SH -f 12000         # maximum size of files created by the shell
# ulimit -l - I don't have permissions ???
# ulimit -SH -l 4000         # maximum size that may be locked into memory
ulimit -SH -m 1            # masimum resident set size
ulimit -SH -n 50            # maximum number of open file descriptions

##ulimit -S -u 10             # max number of processes
#ulimit -SH -p 20           # pipe buffer size
#ulimit -SH -a                 # report on limits




ulimit -S -t 480              # maximum CPU time in seconds

ulimit -SH -s 64000          # maximum stack size
ulimit -SH -v 3200000        # maximum virtual memory per process

ulimit -SH -s 32000          # maximum stack size
ulimit -SH -v 1600000        # maximum virtual memory per process

ulimit -SH -s 16000          # maximum stack size
ulimit -SH -v 800000        # maximum virtual memory per process

ulimit -SH -s 8000          # maximum stack size
ulimit -SH -v 400000        # maximum virtual memory per process

ulimit -SH -s 4000          # maximum stack size
ulimit -SH -v 200000        # maximum virtual memory per process

runSimpleTest BankAccountMain a   # t.testStockConstructor()
runSimpleTest BankAccountMain b   # t.testBalance()
runSimpleTest BankAccountMain c   # t.testCurrentConstructor()
runSimpleTest BankAccountMain d   # t.testToString()
runSimpleTest BankAccountMain e   # t.testDay()
runSimpleTest BankAccountMain f   # t.testOperatorRedir()
runSimpleTest BankAccountMain g   # t.testBuySell()
runSimpleTest BankAccountMain h   # t.testMonth()
runSimpleTest BankAccountMain i   # t.testType()
runSimpleTest BankAccountMain j   # t.testSavingsConstructor()
echo "Finished running all BankAccountMain tests"