#include <iostream>
#include <random>
#include <ratio>
#include <cstdint>

////////////////////////////
///just a test function to test the LED output
// Platzhalter-Definitionen für die Simulation in CLion
void printSpecialOutput(uint16_t input) {
    // Maskiere die Eingabe auf 9 Bit, um Fehler zu vermeiden
    input &= 0x1FF;

    switch (input) {
        case 0b000000001: // Dezimal 1
            std::cout << "-" << std::endl;
            break;

        case 0b000000011: // Dezimal 3
            std::cout << "--" << std::endl;
            break;

        case 0b000000111: // Dezimal 7
            std::cout << "---" << std::endl;
            break;

        case 0b000001111: // Dezimal 15
            std::cout << "----" << std::endl;
            break;

        case 0b000101111: // Dezimal 47 (5. Bit ist das 16er-Bit, hier gesetzt)
            std::cout << "-----" << std::endl;
            break;

        default:
            // Optional: Behandlung für alle anderen Muster
            break;
    }
}

//////////////////////////////////////////

int main() {
    ///////////////////////////////////////////////////////////////////
    // Einmalige Initialisierung des Generators
    std::random_device rd;
    std::mt19937 gen(rd());

    // Verteilung von 0.0 bis 5.0
    // Intervall: [0.0, 5.0)
    std::uniform_real_distribution<double> dist(0.0, 5.0);

    // Testausgabe
    /*for (int n = 0; n < 10; ++n) {
        std::cout << dist(gen) << "\n";
    }*/
    //////////////////////////////////////////////////////////////////////


    //////////////////////////////////////
    //eigentlicher Code://////////////////
    //////////////////////////////////////

    double buffer_array[1000];
    int write = 0; //head of ringbuffer
    int read = 0; //tail of ringbuffer
    double average = 0; //average of the last 1000 numbers

    //save first 1000 Numbers in the array
    for (int i = 0; i < 999; ++i ) {
        //positive value of adc
        double value = dist(gen);
        buffer_array[write] = value * value;
        write = (write + 1 ) % 1000;
    }

    //calculate the first average of the first 1000 numbers
    float sum = 0.0;
    for (int i = 0; i < 1000; ++i ) {//
        sum = sum + buffer_array[i];
    }
    std::cout << sum << "\n";
    average = sum / 1000;
    std::cout << average << "\n";
    std::cout << write << "\n";
    std::cout << read << "\n";


    //other values, loop-function
    while (true) {
        double value = dist(gen);//random value
        read = (read + 1) % 1000;//increase read position
        write = (write + 1) % 1000;//increase write position
        buffer_array[write] = value * value;//writes the actual value in the buffer
        average = average + buffer_array[write]/1000 - buffer_array[read]/1000;


        if(average <=2){printSpecialOutput(0b000000001);}
        else if (average > 2 && average <=4){printSpecialOutput(0b000000011);}
        else if (average > 4 && average <=6){printSpecialOutput(0b000000111);}
        else if (average > 6 && average <=8){printSpecialOutput(0b000001111);}
        else if (average > 8 && average <=10){printSpecialOutput(0b000011111);}
        else if (average > 10 && average <=12){printSpecialOutput(0b000011111);}
        else if (average > 12 && average <=14){printSpecialOutput(0b000011111);}
        else if (average > 14 && average <=16){printSpecialOutput(0b000011111);}
        else{printSpecialOutput(0b000000000);}



    }
}