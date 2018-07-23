package com.agh.console.utils;

public class MathUtil {

    // Method for getting the maximum value
    public static double  getMax(double[] inputArray){
        double maxValue = inputArray[0];

        for(int i=1;i < inputArray.length;i++){

            if(inputArray[i] > maxValue){
                maxValue = inputArray[i];

            }
        }
        return maxValue;
    }

    // Method for getting the minimum value
    public static int getMin(int[] inputArray){
        int minValue = inputArray[0];
        for(int i=1;i<inputArray.length;i++){
            if(inputArray[i] < minValue){
                minValue = inputArray[i];
            }
        }
        return minValue;
    }


    public static double findMaxDifference(double[] arr) {

        double min = arr[0];
        double max = arr[0];

        for (double value : arr) {
            if (min > value) {
                min = value;
            }
            if (max < value) {
                max = value;
            }
        }
        return max - min;
    }

    public static int getIndexOfLargestValue(double[] array) {
        if ( array == null || array.length == 0 ) return -1; // null or empty

        int largest = 0;

        for ( int i = 1; i < array.length; i++ ) {
            if ( array[i] > array[largest] ) largest = i;
        }
        return largest; // position of the first largest found
    }

    public static int getIndexOfSmallestValue(double[] array) {
        if ( array == null || array.length == 0 ) return -1; // null or empty

        int smallest = 0;

        for ( int i = 1; i < array.length; i++ ) {
            if ( array[i] < array[smallest] ) smallest = i;
        }
        return smallest; // position of the first largest found
    }
}
