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

if [ ! -e "CopiedFilesPriority" ]
then
    for file in Priority.h
    do
	cp ../${file} .
    done

    for file in makefile \
	        TesterBase.cpp TesterBase.h \
	        PriorityTester.h PriorityTester.cpp \
                PriorityMain.cpp
    do
	wget "https://campus.cs.le.ac.uk/teaching/resources/CO7105/Worksheets/assessment3/test/${file}" >& /dev/null
    done

    touch CopiedFilesPriority
fi

make PriorityMain &> PriorityCompilation.txt

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

ulimit -SH -s 128000          # maximum stack size
ulimit -SH -v 6400000        # maximum virtual memory per process

runSimpleTest PriorityMain h   # t.testStability()

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

runSimpleTest PriorityMain a   # t.testItInc()
runSimpleTest PriorityMain b   # t.testItAccess()
runSimpleTest PriorityMain c   # t.testPopMix()
runSimpleTest PriorityMain d   # t.testCtor()
runSimpleTest PriorityMain e   # t.testIterator()
runSimpleTest PriorityMain f   # t.testPopSep()
runSimpleTest PriorityMain g   # t.testSame()
echo "Finished running all PriorityMain tests"
