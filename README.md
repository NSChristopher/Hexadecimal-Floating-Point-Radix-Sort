# Hexadecimal Radix Sort

A C implementation of hexadecimal radix sort for 4 byte floating point numbers.

## Description

This is mostly a traditional implementation of radix sort with some adaptions for floating point numbers. The sorting function (floatRadixSort) takes an array of unsined int values (floats that have been cast to uint to preserve their bit patterns) plus a count of the elements in the array and a count of the negative numbers. 

The count of negative numbers is key because it's used to rearange the results after radix sort has run. Radix sort just organizes values into buckets n bytes at a time and since floats are signed, the most significant bit is 0 for positive numbers and 1 for negative numbers which ends up placing the negative numbers after all sorted positive numbers. additionally radix sort places the negative numbers in the wrong order because it only orders them based on their magnitude. with the knowledge we simply use the count of negative numbers to find where they start in the array (negStartIndex = count - negCount - 1) and then add them into the final array in reverse order ahead of the positive numbers.
