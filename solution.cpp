/*
 * INFINITE LENGTH INTEGER ADDER by Louise Fry
 * Created as an assignment for COSC302 at University of Tennessee KNoxville taught by Scott Emrich
 * last update 10/28/2021, 2:41 PM
 *
 * This program uses a stl::queue to read in 2 integers of any length from stdin
 * and prints their sum to stdout. This is ideal for ints or sums of ints greater than "long long".
 */
#include <iostream>
#include <queue>
#include <string>
#include <cmath>
using namespace std;

// prints sum of q1, q2 to stdout
void addIntQueuesAndPrint(queue<int> &q1, queue<int> &q2);

int main(int argc, char *argv[])
{
    string string1, string2;
    queue<int> q1, q2; // I hope this is what you wanted, I wrote it with a typedef initially but it was unneccessary

    // while there is more input to get, get it...
    while (cin >> string1 >> string2)
    {
        // fill the 2 queues with the input.
        char c;
        // iterate thru FIRST int digit by digit and push to the queue
        for (string::reverse_iterator rit = string1.rbegin(); rit != string1.rend(); ++rit)
        {
            c = *rit;             // get a single char from the input string
            q1.push((int)c - 48); // ascii to int conversion
        }

        // iterate thru SECOND int digit by digit and push to the queue
        for (string::reverse_iterator rit = string2.rbegin(); rit != string2.rend(); ++rit)
        {
            c = *rit;             // get a single char from the input string
            q2.push((int)c - 48); // ascii to int conversion
        }

        addIntQueuesAndPrint(q1, q2); // calls addition function

        string1 = ""; // reset for next loop - possibly irrelevant
        string2 = "";
    }
    return 0;
}

// prints sum of q1, q2 to stdout
void addIntQueuesAndPrint(queue<int> &q1, queue<int> &q2)
{
    // add q1, q2 ints together and put in q3
    vector<int> q3; // hope this is acceptable, it's just for printing the sum
    int digitSum = 0;
    int remainder = 0;
    int lengthDiff = 0;
    int carry = 0;

    // loop adding 2 digits together - int addition w carry
    while (!q1.empty() && !q2.empty())
    {
        // do until least ONE of them is empty
        digitSum = q1.front() + q2.front() + carry;

        q1.pop();
        q2.pop();

        // check for carry val
        if (digitSum > 9)
        {
            carry = digitSum / 10;
            remainder = digitSum % 10;

            if (!(q1.empty() && q2.empty())) // comment out this if statement and look at 2nd output - this prevents the extra 0
            {
                q3.push_back(remainder); // MAY be the cause of the error where it carries 10 rather than 1 (failed test case)
            }
            remainder = 0;
        }
        else // no carry val
        {
            carry = 0;
            q3.push_back(digitSum);
        }
    }

    // either q1 or q2 is now empty, but they are not necessarily the same length,
    //  so compare lengths to see if other still has digits in it or if you're done
    lengthDiff = q1.size() - q2.size();

    if (lengthDiff > 0) // then q1 still has values, q2 is empty
    {
        while (!q1.empty())
        {
            digitSum = q1.front() + carry;
            q3.push_back(digitSum);
            q1.pop();
            carry = 0; // carrying impossible after 1st loop since q2 is empty
        }
    }
    else if (lengthDiff < 0) // then q2 still has values, q1 is empty
    {
        while (!q2.empty())
        {
            digitSum = q2.front() + carry;
            q3.push_back(digitSum);
            q2.pop();
            carry = 0; // carrying impossible after 1st loop since q1 is empty
        }
    }

    else if (carry != 0) // else both are empty
    {
        q3.push_back(digitSum); // even if both are empty, the carry may still give you 1 more digit than q1 and q2 had
    }

    // print result, which is in q3
    // iterates backwards in order to print forwards b/c FIFO
    for (int i = q3.size() - 1; i >= 0; i--)
    {
        cout << q3[i];
    }
    cout << endl;
}
