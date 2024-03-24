#include "service.h"
#include <stdio.h>
#include <string.h>

/*
  Function that checks if a continent is valid

*/
bool checkIfContinentIsValid(char continentToBeChecked[])
{
	if (strcmp(continentToBeChecked, "Europe") == 0 || strcmp(continentToBeChecked, "Asia") == 0 || strcmp(continentToBeChecked, "America") == 0 || strcmp(continentToBeChecked, "Australia") == 0 || strcmp(continentToBeChecked, "Africa") == 0)
	{
		return true;
	}
	return false;
}

/*
  Function that adds a country to the repository
*/
int addCountryToService(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository, char nameOfTheCountryToBeAdded[], char continentOfTheCountryToBeAdded[], int populationOfTheCountryToBeAdded)
{
	if (!checkIfContinentIsValid(continentOfTheCountryToBeAdded))
	{
		return 1;
	}
	for (int index = 0; index < countriesRepository->allCountries.size; index++)
		if (strcmp(getCountryName(&countriesRepository->allCountries.elements[index]), nameOfTheCountryToBeAdded) == 0)
			return 2;
	Country newCountry = createNewCountry(nameOfTheCountryToBeAdded, continentOfTheCountryToBeAdded, populationOfTheCountryToBeAdded);
	addUndoElement(undoRedoRepository, countriesRepository);
	addCountryToRepository(countriesRepository, newCountry);
	return 0;
}

/*
  Function that deletes a country from the repository
*/
bool deleteCountryFromService(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository, char nameOfTheCountryToBeDeleted[])
{
	int indexOfTheCountryToBeDeleted = findCountryByItsName(countriesRepository, nameOfTheCountryToBeDeleted);
	if (indexOfTheCountryToBeDeleted == -1)
	{
		return false;
	}
	else
	{
		addUndoElement(undoRedoRepository, countriesRepository);
		deleteCountryFromRepository(countriesRepository, indexOfTheCountryToBeDeleted);
		return true;
	}
}

/*
  Function that updates a country from the repository
*/
int updateCountryFromService(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository, char nameOfTheCountryToBeUpdated[], char newNameOfTheCountryToBeUpdated[], char newContinentOfTheCountryToBeUpdated[], int newPopulationOfTheCountryToBeUpdated)
{
	if (!checkIfContinentIsValid(newContinentOfTheCountryToBeUpdated))
	{
		return 1;
	}
	int indexOfTheCountryToBeUpdated = findCountryByItsName(countriesRepository, nameOfTheCountryToBeUpdated);
	if (indexOfTheCountryToBeUpdated == -1)
	{
		return 2;
	}
	Country updatedCountry = createNewCountry(newNameOfTheCountryToBeUpdated, newContinentOfTheCountryToBeUpdated, newPopulationOfTheCountryToBeUpdated);
	addUndoElement(undoRedoRepository, countriesRepository);
	updateCountryFromRepository(countriesRepository, indexOfTheCountryToBeUpdated, updatedCountry);
	return 0;
}

/*
  Function that returns the length of the repository
*/
int filterByContinent(Repository* countriesRepository, Country validCountriesAfterFiltering[], char continentByWhichToFilter[])
{
	int validCountryCount = 0;
	for (int i = 0; i < countriesRepository->allCountries.size; i++)
	{
		if (strcmp(countriesRepository->allCountries.elements[i].continent, continentByWhichToFilter) == 0)
		{
			validCountriesAfterFiltering[validCountryCount++] = countriesRepository->allCountries.elements[i];
		}
	}
	return validCountryCount;
}
/*
  Function that returns the length of the repository
*/
int filterByTheNameOfTheCountry(Repository* countriesRepository, const char stringByWhichToFilter[], Country* validCountriesAfterFiltering[])
{
	int validCountryCount = 0;
	for (int i = 0; i < countriesRepository->allCountries.size; i++)
	{
		if (stringByWhichToFilter[0] == '\0' || strstr(countriesRepository->allCountries.elements[i].name, stringByWhichToFilter) != NULL) {
			validCountriesAfterFiltering[validCountryCount++] = &countriesRepository->allCountries.elements[i];
		}
	}
	return validCountryCount;
}

/*
  Function that returns the length of the repository
*/
int doMigrationActivity(Repository* countriesRepository, char nameOfCountryFromWhereMigrate[], char nameOfCountryToWhereMigrate[], long int numberOfMigrators)
{
	int indexOfOldCountry = findCountryByItsName(countriesRepository, nameOfCountryFromWhereMigrate);
	int indexOfNewCountry = findCountryByItsName(countriesRepository, nameOfCountryToWhereMigrate);
	if (indexOfOldCountry == -1)
		return 1;
	if (indexOfNewCountry == -1)
		return 2;
	updateInCaseOfMigration(countriesRepository, indexOfOldCountry, indexOfNewCountry, numberOfMigrators);
	return 0;
}

/*
  Function that returns the length of the repository
*/
int filterByContinentAndGreaterPopulationThanGivenValueSortedAscending2(Repository* countriesRepository, Country validCountriesAfterFiltering[], char continentByWhichToFilter[], long int valueThatPopulationShouldBeHigherThan)
{
	int validCountryCount = 0;
	for (int i = 0; i < countriesRepository->allCountries.size; i++)
	{
		if (strcmp(countriesRepository->allCountries.elements[i].continent, continentByWhichToFilter) == 0 && countriesRepository->allCountries.elements[i].population > valueThatPopulationShouldBeHigherThan)
		{
			validCountriesAfterFiltering[validCountryCount++] = countriesRepository->allCountries.elements[i];
		}
	}

	for (int i = 0; i < validCountryCount - 1; i++)
	{
		for (int j = i + 1; j < validCountryCount; j++)
		{
			if (validCountriesAfterFiltering[i].population > validCountriesAfterFiltering[j].population)
			{
				Country temp = validCountriesAfterFiltering[i];
				validCountriesAfterFiltering[i] = validCountriesAfterFiltering[j];
				validCountriesAfterFiltering[j] = temp;
			}
		}
	}

	return validCountryCount;
}

/*
  Function that returns the length of the repository
*/
int filterByContinentAndGreaterPopulationThanGivenValueSortedAscending(Repository* countriesRepository, Country validCountriesAfterFiltering[], char continentByWhichToFilter[], long int valueThatPopulationShouldBeHigherThan) {
	int validCountryCount = 0;
	for (int i = 0; i < countriesRepository->allCountries.size; i++) {
		// Check if the continent is empty or matches the country's continent
		bool isContinentMatch = strlen(continentByWhichToFilter) == 0 || strcmp(countriesRepository->allCountries.elements[i].continent, continentByWhichToFilter) == 0;
		if (isContinentMatch && countriesRepository->allCountries.elements[i].population > valueThatPopulationShouldBeHigherThan) {
			validCountriesAfterFiltering[validCountryCount++] = countriesRepository->allCountries.elements[i];
		}
	}

	// Sort the filtered countries by population in ascending order
	for (int i = 0; i < validCountryCount - 1; i++) {
		for (int j = i + 1; j < validCountryCount; j++) {
			if (validCountriesAfterFiltering[i].population > validCountriesAfterFiltering[j].population) {
				Country temp = validCountriesAfterFiltering[i];
				validCountriesAfterFiltering[i] = validCountriesAfterFiltering[j];
				validCountriesAfterFiltering[j] = temp;
			}
		}
	}

	return validCountryCount;
}

/*
  Function that returns the length of the repository
*/
void sortAllCountriesFromRepoByPopulaitionAscending(Repository* countriesRepository)
{
	for (int i = 0; i < countriesRepository->allCountries.size - 1; i++)
	{
		for (int j = i + 1; j < countriesRepository->allCountries.size; j++)
		{
			if (countriesRepository->allCountries.elements[i].population > countriesRepository->allCountries.elements[j].population)
			{
				Country temp = countriesRepository->allCountries.elements[i];
				countriesRepository->allCountries.elements[i] = countriesRepository->allCountries.elements[j];
				countriesRepository->allCountries.elements[j] = temp;
			}
		}
	}
}

/*
  Function that returns the length of the repository
*/
void sortAllCountriesFromRepoByPopulaitionDescending(Repository* countriesRepository)
{
	for (int i = 0; i < countriesRepository->allCountries.size - 1; i++)
	{
		for (int j = i + 1; j < countriesRepository->allCountries.size; j++)
		{
			if (countriesRepository->allCountries.elements[i].population < countriesRepository->allCountries.elements[j].population)
			{
				Country temp = countriesRepository->allCountries.elements[i];
				countriesRepository->allCountries.elements[i] = countriesRepository->allCountries.elements[j];
				countriesRepository->allCountries.elements[j] = temp;
			}
		}
	}
}

/*
  Function that returns the length of the repository
*/
int filterByContinentAndGreaterPopulationThanGivenValueSortedDescending2(Repository* countriesRepository, Country validCountriesAfterFiltering[], char continentByWhichToFilter[], long int valueThatPopulationShouldBeHigherThan)
{
	int validCountryCount = 0;
	for (int i = 0; i < countriesRepository->allCountries.size; i++)
	{
		if (strcmp(countriesRepository->allCountries.elements[i].continent, continentByWhichToFilter) == 0 && countriesRepository->allCountries.elements[i].population > valueThatPopulationShouldBeHigherThan)
		{
			validCountriesAfterFiltering[validCountryCount++] = countriesRepository->allCountries.elements[i];
		}
	}

	for (int i = 0; i < validCountryCount - 1; i++)
	{
		for (int j = i + 1; j < validCountryCount; j++)
		{
			//sort by population
			//if (strcmp(validCountriesAfterFiltering[i].population, validCountriesAfterFiltering[j].population) < 0)
			if(validCountriesAfterFiltering[i].population < validCountriesAfterFiltering[j].population)
			{
				Country temp = validCountriesAfterFiltering[i];
				validCountriesAfterFiltering[i] = validCountriesAfterFiltering[j];
				validCountriesAfterFiltering[j] = temp;
			}
		}
	}

	return validCountryCount;
}

/*
  Function that returns the length of the repository
*/
int filterByContinentAndGreaterPopulationThanGivenValueSortedDescending(Repository* countriesRepository, Country validCountriesAfterFiltering[], char continentByWhichToFilter[], long int valueThatPopulationShouldBeHigherThan) {
	int validCountryCount = 0;
	for (int i = 0; i < countriesRepository->allCountries.size; i++) {
		// Check if the continent is empty or matches the country's continent
		bool isContinentMatch = strlen(continentByWhichToFilter) == 0 || strcmp(countriesRepository->allCountries.elements[i].continent, continentByWhichToFilter) == 0;
		if (isContinentMatch && countriesRepository->allCountries.elements[i].population > valueThatPopulationShouldBeHigherThan) {
			validCountriesAfterFiltering[validCountryCount++] = countriesRepository->allCountries.elements[i];
		}
	}

	// Sort the filtered countries by population in descending order
	for (int i = 0; i < validCountryCount - 1; i++) {
		for (int j = i + 1; j < validCountryCount; j++) {
			if (validCountriesAfterFiltering[i].population < validCountriesAfterFiltering[j].population) {
				Country temp = validCountriesAfterFiltering[i];
				validCountriesAfterFiltering[i] = validCountriesAfterFiltering[j];
				validCountriesAfterFiltering[j] = temp;
			}
		}
	}

	return validCountryCount;
}

/*
  Function that returns the length of the repository
*/
int ServiceUndo(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository)
{
	if (undoRedoRepository->undoSize == 0)
		return 1;
	addRedoElement(undoRedoRepository, countriesRepository); // add the current repo for the redo operation
	popLastUndo(undoRedoRepository, countriesRepository);
	return 0;
}

/*
  Function that returns the length of the repository
*/
int ServiceRedo(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository)
{
	if (undoRedoRepository->redoSize == 0)
		return 1;
	addUndoElement(undoRedoRepository, countriesRepository); // add the current repo for the undo operation
	popLastRedo(undoRedoRepository, countriesRepository);
	return 0;
}

/*
  Function that returns the length of the repository
*/
void deleteService(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository)
{
	deleteRepository(countriesRepository);
}