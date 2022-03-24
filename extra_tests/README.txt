----------------------------------------------------------------------------

Directions to use these extra tests:

1. Put the contents of this zip file into your project directory
2. Run test.sh script

----------------------------------------------------------------------------
Notes:

1. The script expects to be in the same folder as your executable, and to see a folder named extra_tests.
2. Your executable must be named a.out
3. Tests are named A_B.txt , where A and B are defined in the project document. Knowing this will make your life easier if anything fails.
4. The script will test based on all input in extra_tests, so if you have extra test cases of the same form (like the 2 provided by the professor) you can just drag them into the extra_tests folder and they will work normally.

----------------------------------------------------------------------------

Random tip:
If you want to see what your code outputs for the test cases, you can comment out these two lines of the script
rm -f ${output_file}
rmdir ./output

by putting a # at the start like so
#rm -f ${output_file}
#rmdir ./output

----------------------------------------------------------------------------

How to interpret results:

If you pass all 5 provided tests here, you should pass all 15 on GS, or just 7 and 15.
--If you pass all 15 on GS, you're free.
--If you only pass 7 and 15 on GS, it is likely because:
----you used c++ (you must use c and compile with gcc)
----your zip file contains a folder instead of 4 files (submit just the files without zipping to check this)
----you have a capitalization issue on TCB.h or the line of your code where you include it.
----if it's none of these and you find the solution to it, ping/dm me so I can add it to this file
--If you pass more than 7 and 15 on GS, but not all of them
----ping/dm me so I can add more tests or edit this file with solutions


If you don't pass all 5 here
--Make your ouput match these 5 cases exactly

----------------------------------------------------------------------------

Good Luck!!!
