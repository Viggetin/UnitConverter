/**
 * file:    Converter.c
 * author:  Victor Stén
 * date:    2024-03-24
 * version: 1.0
 *
 * brief: Ohjelman päätarkoitus on tarjota käyttäjälle 3 erinlaista konversio ohjelmaa (pituus, paino ja lämpötila).
 *
 * Tämän ohjelman tarkoitus on tarjota käyttäjälle kolme erinlaista konversio ohjelmaa yhden kokonaisen ohjelman sisällä.
 * Ohjelma alkaa päävalikosta jossa käyttäjälle esitetään käytettävissä olevat vaihtoehdot.
 * Valikossa edetään antamalla komentoja josta päästään haluttuun konversio ohjelmaan. Erinlaisia konversio vaihtoehtoja on kolme
 * pituudet(Metrit, Kilometrit, Mailit), Painot(Kilogramma ja Pauna) ja lämpötilat (Celsius ja Fahrenheit).
 *
 * This software is released under the GPL License.
 */

/* Includes */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Includes */
// Tätä käytetään pääsääntöisesti vasta Konversio syötteen tarkistuksessa jossa tarkastetaan onko syöte validi eli käy vain numerot
#define MaxNum 100

/* Function Prototypes */
void print_logo();
void display_menu(float menuLevel);

//komentojen ja syötteiden anto/tarkistus funktiot
char ask_command();
float sourceInputCheck();

// Yksikkö valintoja ilmoittavat funktiot
void InformUnitTarget(const char *targetUnit, const char *sourceUnit);
void InformUnitSource(const char *sourceUnit);

// Pituus konvertteri funktiot
void convertLength();
float lengthConverter(int sourceChoice, int targetChoice);

// Paino konvertteri funktiot
void convertWeight();
float weightConverter(int sourceChoice, int targetChoice);

// lämpötila konvertteri funktiot
void convertTemperature();
float temperatureConverter(int sourceChoice, int targetChoice);

/* Main Function */
int main(void)
{
    char Output[100];
    char choice;
    float menuLevel;
    menuLevel = 1;

    print_logo();
    display_menu(menuLevel);
    printf("\nGive Command(Main): ");
    choice = ask_command();
    do
    {
        float menuLevel = 1;
        switch (choice)
        {
        case 'A':
            convertLength();
            break;
        case 'B':
            convertWeight();
            break;
        case 'C':
            convertTemperature();
            break;
        case 'D':
            display_menu(menuLevel);
            break;
        case 'X':
            return 0;
            break;
        default:
            printf("Please enter a valid command. To show commands input 'd'\n");
        }

        printf("\nGive Command(Main): ");
        choice = ask_command();
    } while (choice != 'X');

    return 0;
}

/* Functions */
/**
 * Lyhyt selitys ohjelman toiminnasta
 * Funktio printtaa ohjelman alussa esitettävän ASCII kirjaimin tehdyn logon
 */
void print_logo()
{
    printf("  _    _       _ _      _____                          _            \n");
    printf(" | |  | |     (_) |    / ____|                        | |           \n");
    printf(" | |  | |_ __  _| |_  | |     ___  _ ____   _____ _ __| |_ ___ _ __ \n");
    printf(" | |  | | '_ \\| | __| | |    / _ \\| '_ \\ \\ / / _ \\ '__| __/ _ \\ '__|\n");
    printf(" | |__| | | | | | |_  | |___| (_) | | | \\ V /  __/ |  | ||  __/ |   \n");
    printf("  \\____/|_| |_|_|\\__|  \\_____\\___/|_| |_|\\_/ \\___|_|   \\__\\___|_|   \n");
    printf("\n");
}
/**
 * Lyhyt selitys ohjelman toiminnasta
 *
 * Funktion idea on luoda perusteellinen käyttäjä ystävällinen käyttöliittymä.
 * Funktio printtaa ohjelmassa olevat conversio mahdollisuudet jotka määräytyvät sen mukaan missä valikossa käyttäjä on käyttöhetkellä.
 * 
 * Tämä määritellään menuLevel muuttujalla joka vaihtuu joka kerta, kun käyttäjä siirtyy valikosta/ohjelmasta toiseen
 * Valikot on numeroitu 1-4 osaan eli 1 on päävalikko, 2 on Pituus konversio, 3 on paino konversiot ja 4 on lämpötilakonversiot.
 */
void display_menu(float menuLevel)
{
    if (menuLevel == 1)
    {
        printf("A) Length converter (Meters, Kilometers, Miles)\n");
        printf("B) Weight converter (Kilograms, pounds)\n");
        printf("C) Temperature converter(Celsius, Fahrenheit)\n");
        printf("D) Display this menu\n");
        printf("X) Exit the program\n");
        printf("\n");
    }
    else if (menuLevel == 2)
    {
        printf("Please choose your source unit to convert:\n\n");

        printf("A) Meters (m)\n");
        printf("B) Kilometers(Km)\n");
        printf("C) Miles(M)\n");
        printf("X) Exit the Length Converter\n");
    }
    else if (menuLevel == 3)
    {
        printf("Welcome to the Weight converter!\n");
        printf("Please choose your source unit to convert:\n\n");

        printf("A) Kilograms(Km)\n");
        printf("B) Pounds(M)\n");
    }
    else if (menuLevel == 4)
    {
        printf("Welcome to the Temperature converter!\n");
        printf("Please choose your source unit to convert:\n\n");

        printf("A) Celcius (C)\n");
        printf("B) Fahrenheit (F)\n");
    }
}
/**
 * Lyhyt selitys ohjelman toiminnasta
 *
 * Funktio käsittelee käyttöliittymässä annettavien käskyjen suorittamisen
 * Funktio ottaa vastaan vain ennalleen määritettyjä komentoja jota tietyt kirjaimet vastaavat
 * Funktiossa annettu kirjain käsky muutetaan isoksi kirjaimeksi, joka helpottaa ongelmien välttämistä ja parantaa käyttökokemusta.
 * Seuraavaksi annettu käsky tarkistetaan onko kyseinen käsky "Validi" käsky
 *
 * Funktio tarkistaa käskyn if lausekkeella eli onko se tiettyjen kirjainten välistä tai X kirjain.
 * Jos se ei ole funktio jatkaa kysymistä kunnes korrekti käsky on annettu.
 *
 * Ohjelma palauttaa Choice muuttujan funktion lopussa.
 */

char ask_command()
{
    int valid_input = 0;
    char choice;
    do
    {
        scanf(" %c", &choice);
        while (getchar() != '\n')
            ;
        choice = toupper(choice);

        if ((choice < 'A' || choice > 'D') && choice != 'X')
        {
            printf("\nNon-valid input. Please try again.\n");
            printf("If you dont know valid commands input 'D' to the commandline.\n");
            printf("Enter command: ");
            valid_input = 0;
        }
        else
        {
            valid_input = 1;
        }
    } while (!valid_input);

    return choice;
}
/**
 * Lyhyt selitys ohjelman toiminnasta
 *
 * Funktio käsittelee eri pituus yksiköiden konversiota keskenään
 * Funtkio alkaa asettamalla asiaan kuuluvat muuttujat ja myös esittäen listan olemassa olevista vaihtoehdoista.
 *
 * Muuttujat source ja target ovat muuttujia johon tallentuu käyttäjän valinnat.
 * Muuttujia käytetään myöhemmin hyväksi toisessa funktiossa jossa suoritetaan itse konversio.
 * sourceUnit ja targetUnit ovat muuttujia jotka tallentavat mitä yksiköitä käsitellään konversio hetkellä, ennen kun kutsutaan
 * source tai targetInfo funktio jotka kirjottavat oikeaan tapaukseen kuuluvat tekstit käyttäjälle.
 *
 * Ohjelma ei palauta main ohjelmaan mitään vaan kysyy konversion jälkeen haluatko jatkaa vai ei.
 */
void convertLength()
{
    float menuLevel = 2;
    printf("Welcome to the length converter!\n");
    printf("Please choose your source unit to convert:\n\n");

    printf("A) Meters (m)\n");
    printf("B) Kilometers(Km)\n");
    printf("C) Miles(M)\n");

    int choice;
    int sourceChoice;
    int targetChoice;

    char targetUnit;
    char sourceUnit;

    float conversion;
    float meters = 0.0;
    float kilometers = 0.0;
    float miles = 0.0;

    do
    {
        printf("\nGive Command(Lenght Converter): ");
        choice = ask_command();
        // Kysytään lähtöarvo eli --> metri,km vai maili
        switch (choice)
        {
        // Metrit
        case 'A':

            InformUnitSource("Meters");

            sourceChoice = '1';

            printf("A. Kilometers(Km)\n");
            printf("B. Miles(M)\n");

            printf("\nGive Command: ");
            choice = ask_command();
            switch (choice)
            {

            case 'A':
                targetChoice = '1';
                conversion = lengthConverter(sourceChoice, targetChoice);

                printf("That is %.2f kilometers!\n", conversion);

                printf("\nDo you want to convert lengths again?\n");
                printf("If yes press input 'd' or if not input 'x' \n");
                break;
            case 'B':
                targetChoice = '2';
                conversion = lengthConverter(sourceChoice, targetChoice);

                printf("That is %.2f Miles!\n", conversion);

                printf("\nDo you want to convert lengths again?\n");
                printf("If yes press input 'd' or if not input 'x' \n");
                break;
            }
            break;
            // kilometrit
        case 'B':

            InformUnitSource("Kilometers");
            sourceChoice = '2';

            printf("A. Meters(m)\n");
            printf("B. Miles(M)\n");

            printf("\nGive Command: ");
            choice = ask_command();
            switch (choice)
            {
            case 'A':
                targetChoice = '1';
                conversion = lengthConverter(sourceChoice, targetChoice);

                printf("That is %.2f Meters!\n", conversion);

                printf("\nDo you want to convert lengths again?\n");
                printf("If yes press input 'd' or if not input 'x' \n");
                break;
            case 'B':
                targetChoice = '2';
                conversion = lengthConverter(sourceChoice, targetChoice);
                printf("That is %.2f Miles!\n", conversion);

                printf("\nDo you want to convert lengths again?\n");
                printf("If yes press input 'd' or if not input 'x' \n");
                break;
            }
            break;
        // Mailit
        case 'C':

            InformUnitSource("Miles");

            sourceChoice = '3';

            printf("A. Meters(m)\n");
            printf("B. Kilometers(Km)\n");

            printf("\nGive Command: ");
            choice = ask_command();
            switch (choice)
            {
            // Miles to meters
            case 'A':
                targetChoice = '1';
                conversion = lengthConverter(sourceChoice, targetChoice);

                printf("That is %.2f Meters!\n", conversion);

                printf("\nDo you want to convert lengths again?\n");
                printf("If yes press input 'd' or if not input 'x' \n");
                break;
            // Miles to Kilometers
            case 'B':
                targetChoice = '2';
                conversion = lengthConverter(sourceChoice, targetChoice);
                printf("That is %.2f Kilometers!\n", conversion);

                printf("\nDo you want to convert lengths again?\n");
                printf("If yes press input 'd' or if not input 'x' \n");
                break;
            }
            break;
        case 'D':
            display_menu(menuLevel);
            break;
        case 'X':
            break;
        default:
            printf("Please enter a valid command. To show commands input 'd'\n");
        }

    } while (choice != 'X');
}
/*
 * Lyhyt selitys ohjelman toiminnasta
 *
 * Funktio ottaa vastaan convertLength funktiosta kaksi muuttujaa vastaan eli sourceChoice ja targetChoice.
 * Näitä muuttujia hyödyntäen funktio voi if lausekkeita käyttäen löytää oikean polun oikeaan konvertteriin, jossa vasta kysytään käyttäjän source yksikön syöte arvo.
 * Tätä arvoa käyttäen lasketaan kyseiseen konversioon liittyvä lasku josta lopulta esitetään konversion lopputulos käyttäjälle.
 * Ohjelma palautuu konvertterin valikkoon ja kysyy myös haluaako käyttäjä konvertoida uudestaan vastaavaa suuretta.
 *
 * Ohjelma paluttaa konversion edelliseen funktioon käyttäjälle näkyväksi.
 */
float lengthConverter(int sourceChoice, int targetChoice)
{
    float meters = 0.0;
    float kilometers = 0.0;
    float miles = 0.0;
    float conversion;
    if (sourceChoice == '1')
    {
        // A --> Meters to Km
        if (targetChoice == '1')
        {
            InformUnitTarget("Kilometers", "meters");
            meters = sourceInputCheck();
            conversion = (float)meters / 1000;
            return conversion;
        }
        // B--> Meters to Miles
        else if (targetChoice == '2')
        {
            InformUnitTarget("Miles", "meters");
            meters = sourceInputCheck();
            conversion = (float)meters * 0.0006213712;
            return conversion;
        }
    }
    else if (sourceChoice == '2')
    {
        // A --> Km to m
        if (targetChoice == '1')
        {
            InformUnitTarget("Meters", "Kilometers");
            kilometers = sourceInputCheck();
            conversion = (float)kilometers * 1000;
            return conversion;
        }
        // B--> Km to M
        else if (targetChoice == '2')
        {
            InformUnitTarget("Miles", "Kilometers");
            kilometers = sourceInputCheck();
            conversion = (float)kilometers * 0.621371192;
            return conversion;
        }
    }
    else if (sourceChoice == '3')
    { // B--> M to m
        if (targetChoice == '1')
        {
            InformUnitTarget("Meters", "Miles");
            miles = sourceInputCheck();
            conversion = (float)miles * 1609.344;
            return conversion;
        }
        // B--> M to Km
        else if (targetChoice == '2')
        {
            InformUnitTarget("Kilometers", "Miles");
            miles = sourceInputCheck();
            conversion = (float)miles * 1.609344;
            return conversion;
        }
    }
}
/**
 * Lyhyt selitys ohjelman toiminnasta
 *
 *Funktion tarkoitus on helpottaa yksikkö tekstien printtaamista eri konversioihin, että ei tarvitse kovakoodata kaikkea samaan.
 *
 * Funktion syötteinä toimii itse konversio vaihtoehdoissa mainitut yksiköt jotka on kovakoodattu jokaiseen kohtaan tällä hetkellä...
 *
 * Ohjelma paluttaa oikean printin sen syötteiden perusteella
 */
void InformUnitTarget(const char *targetUnit, const char *sourceUnit)
{

    printf("You have selected %s as the target unit.\n", targetUnit);
    printf("Please enter a value in %s to convert it to %s : ", sourceUnit, targetUnit);
}
/**
 * Lyhyt selitys ohjelman toiminnasta
 *
 *Funktion tarkoitus sama kuin InformTarget funktiossa mutta tässä tapauksessa printataan lähdearvoon liittyvät tiedot.
 *Funktio ottaa myös vain sourceUnit muuttujan vastaan koska se ei tarvitse targetUnittia printissä.
 */
void InformUnitSource(const char *sourceUnit)
{

    printf("You have selected %s as your source unit\n", sourceUnit);
    printf("Please select the target unit:\n");
}

/*
 *Funktio käsittelee eri paino yksiköiden konversiota keskenään
 * Funtkio alkaa asettamalla asiaan kuuluvat muuttujat ja myös esittäen listan olemassa olevista vaihtoehdoista.
 *
 * Muuttujat source ja target ovat muuttujia johon tallentuu käyttäjän valinnat.
 * Muuttujia käytetään myöhemmin hyväksi toisessa funktiossa jossa suoritetaan itse konversio.
 * sourceUnit ja targetUnit ovat muuttujia jotka tallentavat mitä yksiköitä käsitellään konversio hetkellä, ennen kun kutsutaan
 * source tai targetInfo funktio jotka kirjottavat oikeaan tapaukseen kuuluvat tekstit käyttäjälle.
 *
 * Ohjelma ei palauta main ohjelmaan mitään vaan kysyy konversion jälkeen haluatko jatkaa vai ei.
 */
void convertWeight()
{
    float menuLevel = 3;
    printf("Welcome to the Weight converter!\n");
    printf("Please choose your source unit to convert:\n\n");

    printf("A) Kilograms(Km)\n");
    printf("B) Pounds(M)\n");

    int choice;
    int sourceChoice;
    int targetChoice;

    char targetUnit;
    char sourceUnit;

    float conversion;
    float kilograms = 0.0;
    float pounds = 0.0;

    do
    {
        printf("\nGive Command(Weight Converter): ");
        choice = ask_command();
        // Kysytään lähtöarvo eli --> Kilogramma tai pauna
        switch (choice)
        {
        // Kilogramma
        case 'A':

            InformUnitSource("Kilogram");

            sourceChoice = '1';

            printf("A. Pounds\n");

            printf("\nGive Command: ");
            choice = ask_command();
            switch (choice)
            {
                //Kg -> pounds
            case 'A':
                targetChoice = '1';
                conversion = weightConverter(sourceChoice, targetChoice);

                printf("That is %.2f lbs!\n", conversion);

                printf("\nDo you want to convert weigths again?\n");
                printf("If yes press input 'd' or if not input 'x' \n");
                break;
            }
            break;
            // Paunat
        case 'B':

            InformUnitSource("Pounds");
            sourceChoice = '2';

            printf("A. Kilograms(Kg)\n");

            printf("\nGive Command: ");
            choice = ask_command();
            switch (choice)
            {
                //pounds --> Kg
            case 'A':
                targetChoice = '1';
                conversion = weightConverter(sourceChoice, targetChoice);

                printf("That is %.2f Kg!\n", conversion);

                printf("\nDo you want to convert weigths again?\n");
                printf("If yes press input 'd' or if not input 'x' \n");
                break;
            }
            break;
        case 'D':
            display_menu(menuLevel);
            break;
        case 'X':
            break;
        default:
            printf("Please enter a valid command. To show commands input 'd'\n");
        }

    } while (choice != 'X');
}

/*
 * Lyhyt selitys ohjelman toiminnasta
 *
 * Funktio ottaa vastaan convertWeigth funktiosta kaksi muuttujaa vastaan eli sourceChoice ja targetChoice.
 * Näitä muuttujia hyödyntäen funktio voi if lausekkeita käyttäen löytää oikean polun oikeaan konvertteriin, jossa vasta kysytään käyttäjän source yksikön syöte arvo.
 * Tätä arvoa käyttäen lasketaan kyseiseen konversioon liittyvä lasku josta lopulta esitetään konversion lopputulos käyttäjälle.
 * Ohjelma palautuu konvertterin valikkoon ja kysyy myös haluaako käyttäjä konvertoida uudestaan vastaavaa suuretta.
 *
 * Ohjelma paluttaa konversion edelliseen funktioon käyttäjälle näkyväksi.
 */

float weightConverter(int sourceChoice, int targetChoice)
{

    float kilogram = 0.0;
    float pounds = 0.0;

    float conversion;
    if (sourceChoice == '1')
    {
        // A --> Kilograms to Pounds
        if (targetChoice == '1')
        {
            InformUnitTarget("Pounds", "Kilograms");
            kilogram = sourceInputCheck();
            conversion = (float)kilogram / 0.45359237;
            return conversion;
        }
    }
    else if (sourceChoice == '2')
    {
        // B --> Pounds to Kilograms
        if (targetChoice == '1')
        {
            InformUnitTarget("Kilograms", "Pounds");
            pounds = sourceInputCheck();
            conversion = (float)pounds * 0.45359237;
            return conversion;
        }
    }
}
/*
 *Funktio käsittelee eri lämpötila yksiköiden konversiota keskenään
 * Funtkio alkaa asettamalla asiaan kuuluvat muuttujat ja myös esittäen listan olemassa olevista vaihtoehdoista.
 *
 * Muuttujat source ja target ovat muuttujia johon tallentuu käyttäjän valinnat.
 * Muuttujia käytetään myöhemmin hyväksi toisessa funktiossa jossa suoritetaan itse konversio.
 * sourceUnit ja targetUnit ovat muuttujia jotka tallentavat mitä yksiköitä käsitellään konversio hetkellä, ennen kun kutsutaan
 * source tai targetInfo funktio jotka kirjottavat oikeaan tapaukseen kuuluvat tekstit käyttäjälle.
 *
 * Ohjelma ei palauta main ohjelmaan mitään vaan kysyy konversion jälkeen haluatko jatkaa vai ei.
 */
void convertTemperature()
{
    float menuLevel = 4;
    printf("Welcome to the Temperature converter!\n");
    printf("Please choose your source unit to convert:\n\n");

    printf("A) Celcius (C)\n");
    printf("B) Fahrenheit (F)\n");

    int choice;
    int sourceChoice;
    int targetChoice;

    char targetUnit;
    char sourceUnit;

    float conversion;
    float celsius = 0.0;
    float fahrenheit = 0.0;

    do
    {
        printf("\nGive Command(Temperature converter): ");
        choice = ask_command();
        // Kysytään lähtöarvo eli --> celcius vai fahrenheit
        switch (choice)
        {
        // Celcius
        case 'A':

            InformUnitSource("Celsius");

            sourceChoice = '1';

            printf("A. Fahrenheit\n");

            printf("\nGive Command: ");
            choice = ask_command();
            switch (choice)
            {

            case 'A':
                targetChoice = '1';
                conversion = temperatureConverter(sourceChoice, targetChoice);

                printf("That is %.2f F!\n", conversion);

                printf("\nDo you want to convert temperatures again?\n");
                printf("If yes press input 'd' or if not input 'x' \n");
                break;
            }
            break;
            // Fahrenheit
        case 'B':

            InformUnitSource("Fahrenheit");
            sourceChoice = '2';

            printf("A. Celsius\n");

            printf("\nGive Command: ");
            choice = ask_command();
            switch (choice)
            {
            case 'A':
                targetChoice = '1';
                conversion = temperatureConverter(sourceChoice, targetChoice);

                printf("That is %.2f C!\n", conversion);

                printf("\nDo you want to convert temperatures again?\n");
                printf("If yes press input 'd' or if not input 'x' \n");
                break;
            }
            break;
        case 'D':
            display_menu(menuLevel);
            break;
        case 'X':
            break;
        default:
            printf("Please enter a valid command. To show commands input 'd'\n");
        }

    } while (choice != 'X');
}
/*
 * Lyhyt selitys ohjelman toiminnasta
 *
 * Funktio ottaa vastaan convertTemperature funktiosta kaksi muuttujaa vastaan eli sourceChoice ja targetChoice.
 * Näitä muuttujia hyödyntäen funktio voi if lausekkeita käyttäen löytää oikean polun oikeaan konvertteriin, jossa vasta kysytään käyttäjän source yksikön syöte arvo.
 * Tätä arvoa käyttäen lasketaan kyseiseen konversioon liittyvä lasku josta lopulta esitetään konversion lopputulos käyttäjälle.
 * Ohjelma palautuu konvertterin valikkoon ja kysyy myös haluaako käyttäjä konvertoida uudestaan vastaavaa suuretta.
 *
 * Ohjelma paluttaa konversion edelliseen funktioon käyttäjälle näkyväksi.
 */
float temperatureConverter(int sourceChoice, int targetChoice)
{
    {

        float celsius = 0.0;
        float fahrenheit = 0.0;

        float conversion;
        if (sourceChoice == '1')
        {
            // A --> celsius to fahrenheit
            if (targetChoice == '1')
            {
                InformUnitTarget("Fahrenheit", "Celsius");
                celsius = sourceInputCheck();
                conversion = (float)(celsius * 9 / 5) + 32;
                return conversion;
            }
        }
        else if (sourceChoice == '2')
        {
            // B --> fahrenheit to celsius
            if (targetChoice == '1')
            {
                InformUnitTarget("Celsius", "Fahrenheit");
                fahrenheit = sourceInputCheck();
                conversion = (float)(fahrenheit - 32) * 5 / 9;
                return conversion;
            }
        }
    }
}

/*
 * Lyhyt selitys ohjelman toiminnasta
 *
 * 
 *
 * Ohjelma paluttaa tarkistetun syötteen jos kyseinen syöte sisältää vain numeroita. 
 * Jos käyttäjä syöttää kirjaimia tai muita merkkejä niin funktio kehottaa syöttämään numeroita.
 */
float sourceInputCheck() {
    char userInput[50];
    float input = 0.0;

    while (input == 0.0) {
        fgets(userInput, MaxNum, stdin);

        if (sscanf(userInput, "%f", &input) != 1) {
            input = 0.0;
            printf("Invalid input. Please enter only numbers.\n");
        }
    }

    return input;
}
/**
 * brief: License Information
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */