#define _CRT_SECURE_NO_WARNINGS
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

/*
  Function that displays all the countries from the repository
*/
void displayAllCountries(Repository* countriesRepository)
{
    int index;
    for (index = 0; index < getDynamicArraySize(&countriesRepository->allCountries); index++)
        printf("#%d Country: %s, Continent: %s, Population: %ld \n", index + 1, countriesRepository->allCountries.elements[index].name, countriesRepository->allCountries.elements[index].continent, countriesRepository->allCountries.elements[index].population);

}

/*
  Function that adds a country to the repository
*/
void addNewCountryUi(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository)
{
    char nameOfTheCountryToBeAdded[50];
    char continentOfTheCountryToBeAdded[50];
    char populationOfTheCountryToBeAdded[50] = "";
    printf("Name of the country: ");
    scanf(" %s", &nameOfTheCountryToBeAdded);
    printf("Name of the continent: ");
    scanf("%s", &continentOfTheCountryToBeAdded);
    printf("Population: ");
    scanf("%s", &populationOfTheCountryToBeAdded);
    long int populationOfTheCountryToBeAddedIntegerValue = strtol(populationOfTheCountryToBeAdded, NULL, 10);
    int addedStatus = addCountryToService(countriesRepository, undoRedoRepository, nameOfTheCountryToBeAdded, continentOfTheCountryToBeAdded, populationOfTheCountryToBeAddedIntegerValue);
    if (addedStatus == 2)
        printf("Country %s already exists in the list.\n", nameOfTheCountryToBeAdded);
    else if (addedStatus == 1)
        printf("The continent %s is not a valid one.\n", continentOfTheCountryToBeAdded);
    else
        printf("Country %s successfully added.\n", nameOfTheCountryToBeAdded);
}

/*
  Function that deletes a country from the repository
*/
void deleteCountryUi(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository)
{
    char nameOfTheCountryToBeDeleted[50];
    printf("Enter the name of the country you want to delete: ");
    scanf(" %s", &nameOfTheCountryToBeDeleted);
    bool deletedStatus = deleteCountryFromService(countriesRepository, undoRedoRepository, nameOfTheCountryToBeDeleted);
    if (deletedStatus == false)
        printf("The country you wanted to delete is not in the list.\n");
    else
        printf("Entry %s successfully deleted.\n", nameOfTheCountryToBeDeleted);
}

/*
  Function that updates a country from the repository
*/
void updateCountryUi(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository)
{
    char updateOption[5] = "\0";
    printf("Choose a type of update: \n"
        "1. Update name, continent and/or population.\n"
        "2. Migration. \n");
    scanf("%s", &updateOption);
    int updateOptionIntegerValue = strtol(updateOption, NULL, 10);
    if (updateOptionIntegerValue == 1) {
        char nameOfTheOldCountry[50];
        char nameOfTheNewCountry[50];
        char continentOfTheNewCountry[50];
        char populationOfTheNewCountry[50] = "";
        long int populationOfTheNewCountryIntegerValue;
        printf("Old name of the country: ");
        scanf("%s", &nameOfTheOldCountry);
        printf("New name of the country: ");
        scanf("%s", &nameOfTheNewCountry);
        printf("Continent of the country: ");
        scanf("%s", &continentOfTheNewCountry);
        printf("Population of the country: ");
        scanf("%s", &populationOfTheNewCountry);
        populationOfTheNewCountryIntegerValue = strtol(populationOfTheNewCountry, NULL, 10);
        int updatedStatus = updateCountryFromService(countriesRepository, undoRedoRepository, nameOfTheOldCountry, nameOfTheNewCountry, continentOfTheNewCountry, populationOfTheNewCountryIntegerValue);
        if (updatedStatus == 2)
            printf("Country %s does not exist.\n", nameOfTheNewCountry);
        else if (updatedStatus == 1)
            printf("Invalid input for the continent.\n");
        else
            printf("Country %s successfully updated.\n", nameOfTheOldCountry);
    }

    else if (updateOptionIntegerValue == 2) {
        char nameOfTheOldCountry[50];
        char nameOfTheNewCountry[50];
        char numberOfMigrators[50] = "";
        printf("Name of the country from where to migrate: ");
        scanf("%s", &nameOfTheOldCountry);
        printf("Name of the country to where to migrate: ");
        scanf("%s", &nameOfTheNewCountry);
        printf("Number of migrators: ");
        scanf("%s", &numberOfMigrators);
        long int numberOfMigratorsIntegerValue = strtol(numberOfMigrators, NULL, 10);
        int updatedStatus = doMigrationActivity(countriesRepository, nameOfTheOldCountry, nameOfTheNewCountry, numberOfMigratorsIntegerValue);
        if (updatedStatus == 1)
            printf("Country %s does not exist.\n", nameOfTheOldCountry);
        else if (updatedStatus == 2)
            printf("Country %s does not exist. \n", nameOfTheNewCountry);
        else
            printf("%ld people migrated from %s to %s.\n", numberOfMigratorsIntegerValue, nameOfTheOldCountry, nameOfTheNewCountry);

    }
}

/*
  Function that displays all the countries from a given continent
*/
void displayAllCountriesFromContinent(Repository* countriesRepository)
{
    char continent[50];
    printf("Enter continent name: ");
    scanf("%s", &continent);
    Country validCountriesAfterFiltering[50];
    int validCountriesCounter = filterByContinent(countriesRepository, validCountriesAfterFiltering, continent);
    if (validCountriesCounter == 0)
        printf("There are no countries on the given continent.\n");
    else
    {
        for (int index = 0; index < validCountriesCounter; index++)
            printf("#%d Country: %s, continent: %s, population: %ld \n", index + 1, validCountriesAfterFiltering[index].name, validCountriesAfterFiltering[index].continent, validCountriesAfterFiltering[index].population);
    }
}

/*
  Function that displays all the countries from the repository whose name contains a given string
*/
void searchCountryByNameUi(Repository* countriesRepository) {
    char stringByWhichToFilter[50] = { 0 };
    Country* validCountriesAfterFiltering[50];

    printf("Enter the string by which you want to filter (press enter for no filter): \n");
    scanf("%*[^\n]"); //  reads and discards all characters until it finds a newline, but does not store them (* means ignore/discard).
    scanf("%*c"); // to discard the newline itself
    fgets(stringByWhichToFilter, 50, stdin); // Use fgets to allow empty input  
    stringByWhichToFilter[strcspn(stringByWhichToFilter, "\n")] = 0; // Remove trailing newline

    int validCountriesCounter = filterByTheNameOfTheCountry(countriesRepository, stringByWhichToFilter, validCountriesAfterFiltering);
    if (validCountriesCounter == 0)
        printf("There are no countries that match the criteria.\n");
    else {
        for (int index = 0; index < validCountriesCounter; index++)
            printf("#%d Country: %s, continent: %s, population: %ld \n", index + 1, validCountriesAfterFiltering[index]->name, validCountriesAfterFiltering[index]->continent, validCountriesAfterFiltering[index]->population);
    }
}

/*
  Function that filters the countries by continent and sorts them by population
*/  
void filterCountryByContinentAndSortByPopulationGreaterThanValueUi2(Repository* countriesRepository)
{
    char continent[50];
    char population[50];
    Country filteredCountries[50];
    int filteredCount = 0;

    printf("Sorted ascending or descending?\n");
    printf("1. Ascending\n");
    printf("2. Descending\n");
    int option;
    scanf("%d", &option);

    printf("Enter population value: ");
    scanf("%s", &population);
    long int populationINT = strtol(population, NULL, 10); // strtol converts a string to a long int with base 10


    printf("Enter continent name: ");
    scanf("%s", &continent);
    
    if (option == 1)
        filteredCount = filterByContinentAndGreaterPopulationThanGivenValueSortedAscending(countriesRepository, filteredCountries, continent, populationINT);
    else if (option == 2)
        filteredCount = filterByContinentAndGreaterPopulationThanGivenValueSortedDescending(countriesRepository, filteredCountries, continent, populationINT);
    else
        printf("Invalid option. Please try again.\n");

    if (filteredCount == 0) {
        printf("No countries found matching the specified criteria.\n");
        return;
    }
    else
    {
        printf("Found %d countries matching the specified criteria:\n", filteredCount);

        for (int index = 0; index < filteredCount; index++)
            printf("#%d Country: %s, continent: %s, population: %ld \n", index + 1, filteredCountries[index].name, filteredCountries[index].continent, filteredCountries[index].population);
    }
}

/*
  Function that filters the countries by continent and sorts them by population
*/
void filterCountryByContinentAndSortByPopulationGreaterThanValueUi(Repository* countriesRepository) {
    char continent[50] = { 0 };
    char populationStr[50];
    Country filteredCountries[50];
    int filteredCount = 0;

    printf("Sorted ascending or descending?\n");
    printf("1. Ascending\n");
    printf("2. Descending\n");
    int option;
    scanf("%d", &option);
    // Clear the input buffer
    while (getchar() != '\n');

    printf("Enter population value: ");
    fgets(populationStr, sizeof(populationStr), stdin);
    long int population = strtol(populationStr, NULL, 10);

    printf("Enter continent name (press enter for all continents): ");
    fgets(continent, sizeof(continent), stdin);

    // Remove the newline character if present
    continent[strcspn(continent, "\n")] = 0;

    if (option == 1) {
        filteredCount = filterByContinentAndGreaterPopulationThanGivenValueSortedAscending(countriesRepository, filteredCountries, continent, population);
    }
    else if (option == 2) {
        filteredCount = filterByContinentAndGreaterPopulationThanGivenValueSortedDescending(countriesRepository, filteredCountries, continent, population);
    }
    else {
        printf("Invalid option. Please try again.\n");
        return;
    }

    if (filteredCount == 0) {
        printf("No countries found matching the specified criteria.\n");
    }
    else {
        printf("Found %d countries matching the specified criteria:\n", filteredCount);
        for (int i = 0; i < filteredCount; i++) {
            printf("#%d Country: %s, Continent: %s, Population: %ld\n", i + 1, filteredCountries[i].name, filteredCountries[i].continent, filteredCountries[i].population);
        }
    }
}

/*
  Function that frees the memory
*/
void freeUi(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository)
{
    deleteService(countriesRepository, undoRedoRepository);
	printf("\nMenu exited successfully.\n");
}

/*
  Function that undoes the last operation
*/
void undoUi(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository)
{
    int validityChecker = ServiceUndo(countriesRepository, undoRedoRepository);
    if (validityChecker == 1)
        printf("There are no more operations that can be undone!\n");
    else
        printf("Last operation was undone!\n");
}

/*
  Function that redoes the last operation
*/
void redoUi(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository)
{
    int validityChecker = ServiceRedo(countriesRepository, undoRedoRepository);
    if (validityChecker == 1)
        printf("There are no more operations that can be redone!\n");
    else
        printf("Last operation was redone!\n");
}

/*
  Function that prints the menu
*/
void printMenu()
{
    printf("        MENU \n\n"
        "1. Display all countries whose name contains a given string.(enter for displaying everything) \n"
        "2. Add a country. \n"
        "3. Delete a country. \n"
        "4. Update a country. \n"
        "5. Display all countries on a given continent, whose populations are greater than a given value. (ascending/descending) \n"
        "6. Undo. \n"
        "7. Redo. \n"
        "8. Filter countries by continent(Bonus).\n"
        "0. Exit. \n"
    );
}

/*
  Function that starts the application
*/
void startApplication()
{
    int optionChosenByTheUser = -1;
    Repository countriesRepository = createRepository();
    UndoRedoRepository undoRedoRepository = createUndoRedoRepository(10);
    printMenu();
    while (optionChosenByTheUser != 0) {
        //printMenu();
        printf("\nEnter your option: ");
        if (scanf("%d", &optionChosenByTheUser) != 1)
        {
            optionChosenByTheUser = -1;
            while (getchar() != '\n') {}
            printf("Invalid input. Please enter a valid option.\n");
            continue;
        }
        switch (optionChosenByTheUser) {
        case 1:
            searchCountryByNameUi(&countriesRepository);
            break;
        case 2:
            addNewCountryUi(&countriesRepository, &undoRedoRepository);
            break;
        case 3:
            deleteCountryUi(&countriesRepository, &undoRedoRepository);
            break;
        case 4:
            updateCountryUi(&countriesRepository, &undoRedoRepository);
            break;
        case 5:
            filterCountryByContinentAndSortByPopulationGreaterThanValueUi(&countriesRepository);
            break;
        case 6:
            undoUi(&countriesRepository, &undoRedoRepository);
            break;
        case 7:
            redoUi(&countriesRepository, &undoRedoRepository);
            break;
        case 8:
            displayAllCountriesFromContinent(&countriesRepository);
            break;
        case 0:
            freeUi(&countriesRepository, &undoRedoRepository);
            exit(0);
        default:
            printf("Invalid option. Please try again.\n");
        }
    }


}