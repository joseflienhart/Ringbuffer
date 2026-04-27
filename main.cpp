#include <iostream>
#include <random>
#include <ratio>

int main() {
    ///////////////////////////////////////////////////////////////////
    // Einmalige Initialisierung des Generators
    std::random_device rd;
    std::mt19937 gen(rd());

    // Verteilung von 0.0 bis 5.0
    // Intervall: [0.0, 5.0)
    std::uniform_real_distribution<double> dist(0.0, 5.0);

    // Testausgabe
    for (int n = 0; n < 10; ++n) {
        std::cout << dist(gen) << "\n";
    }
    //////////////////////////////////////////////////////////////////////


    //////////////////////////////////////
    //eigentlicher Code://////////////////
    //////////////////////////////////////

    double buffer_array[1000];
    int write = 0; //head of ringbuffer
    int read = 0; //tail of ringbuffer
    double average = 0; //average of the last 1000 numbers


    //Save numbers in the array
    buffer_array[write] = 1;
    write = (write + 1) % 1000;

    //save first 1000 Numbers in the array
    for (int i = 0; i < 1000; ++i ) {
        //positive value of adc
        double value = dist(gen);
        buffer_array[write] = value * value;
        write = (write + 1 ) % 1000;
    }

    //calculate the first average
    for (int i = 0; i < 999; ++i ) {//
        average = average + buffer_array[i];
    }
    average = average / 1000;


    //other values
    while (true) {
        double value = dist(gen);//random value
        read = (read + 1) % 1000;//increase read position
        write = (write + 1) % 1000;//increase write position
        buffer_array[write] = value * value;//write the actual value in the buffer
        average = average + buffer_array[write]/1000> - buffer_array[read]/1000;
    }








}