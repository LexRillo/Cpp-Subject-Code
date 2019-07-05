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

if [ ! -e "CopiedFilesState" ]
then
    for file in State.cpp State.h
    do
	cp ../${file} .
    done
    
    for file in makefile \
	        TesterBase.cpp TesterBase.h \
	        Transition.h Transition.cpp \
	        ModelState.h \
	        StateTester.h StateTester.cpp \
                StateMain.cpp
    do
	wget "https://campus.cs.le.ac.uk/teaching/resources/CO7105/Worksheets/assessment1/test/${file}" >& /dev/null
    done

    touch CopiedFilesState
fi

make StateMain &> StateCompilation.txt


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

runSimpleTest StateMain j   # t.testMoveMemory()

ulimit -SH -s 16000          # maximum stack size
ulimit -SH -v 800000        # maximum virtual memory per process

ulimit -SH -s 8000          # maximum stack size
ulimit -SH -v 400000        # maximum virtual memory per process

ulimit -SH -s 4000          # maximum stack size
ulimit -SH -v 200000        # maximum virtual memory per process

runSimpleTest StateMain a   # t.testAssignmentOpMove()
runSimpleTest StateMain b   # t.testOpEq()
runSimpleTest StateMain c   # t.testTransition()
runSimpleTest StateMain d   # t.testName()
runSimpleTest StateMain e   # t.testCtor()
runSimpleTest StateMain f   # t.testLabel()
runSimpleTest StateMain g   # t.testAssignmentOpCopy()
runSimpleTest StateMain h   # t.testMoveCtor()
runSimpleTest StateMain i   # t.testCopyCtor()
runSimpleTest StateMain k   # t.testStability()
echo "Finished running all StateMain tests"
