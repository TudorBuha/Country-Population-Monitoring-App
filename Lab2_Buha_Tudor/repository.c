#include <stdio.h>
#include <string.h>
#include "repository.h"

/*
  Function that initialises the repository with ten entries
*/
void initialiseRepositoryWithTenEntries(Repository* countriesRepository)
{
	Country country1 = createNewCountry("Belgium", "Europe", 79);
	Country country2 = createNewCountry("Portugal", "Europe", 77);
	Country country3 = createNewCountry("Mexico", "America", 32);
	Country country4 = createNewCountry("Japan", "Asia", 87);
	Country country5 = createNewCountry("South Africa", "Africa", 7);
	Country country6 = createNewCountry("Australia", "Australia", 9);
	Country country7 = createNewCountry("Romania", "Europe", 12);
	Country country8 = createNewCountry("Canada", "America", 34);
	Country country9 = createNewCountry("Nigeria", "Africa", 89);
	Country country10 = createNewCountry("Jordan", "Asia", 1);
	addCountryToRepository(countriesRepository, country1);
	addCountryToRepository(countriesRepository, country2);
	addCountryToRepository(countriesRepository, country3);
	addCountryToRepository(countriesRepository, country4);
	addCountryToRepository(countriesRepository, country5);
	addCountryToRepository(countriesRepository, country6);
	addCountryToRepository(countriesRepository, country7);
	addCountryToRepository(countriesRepository, country8);
	addCountryToRepository(countriesRepository, country9);
	addCountryToRepository(countriesRepository, country10);
}

/*
  Function that creates a new repository
*/
Repository createRepository()
{
	Repository countriesRepository;
	DynamicArray* initialDynamicArray = createDynamicArray(10);
	countriesRepository.allCountries = *initialDynamicArray;
	initialiseRepositoryWithTenEntries(&countriesRepository);
	return countriesRepository;
}

/*
  Function that adds a country to the repository
*/
void addCountryToRepository(Repository* countriesRepository, Country countryToBeAdded)
{
	addElement(&countriesRepository->allCountries, countryToBeAdded);
}

/*
  Function that deletes a country from the repository
*/
void deleteCountryFromRepository(Repository* countriesRepository, int indexOfTheCountryToBeDeleted)
{
	deleteElement(&countriesRepository->allCountries, indexOfTheCountryToBeDeleted);
}

/*
  Function that updates a country from the repository
*/
void updateCountryFromRepository(Repository* countriesRepository, int indexOfTheCountryToBeUpdated, Country countryWithUpdatedData)
{
	updateElement(&countriesRepository->allCountries, indexOfTheCountryToBeUpdated, countryWithUpdatedData);
}

/*
  Function that returns the length of the repository
*/
void updateInCaseOfMigration(Repository* countriesRepository, int indexOfOldCountry, int indexOfNewCountry, long int numberOfMigrators)
{
	countriesRepository->allCountries.elements[indexOfOldCountry].population -= numberOfMigrators;
	countriesRepository->allCountries.elements[indexOfNewCountry].population += numberOfMigrators;
}

/*
  Function that returns the length of the repository
*/
int findCountryByItsName(Repository* countriesRepository, char stringThatIsBeingSearched[])
{
	int indexOfTheSearchedCountry = -1;
	int currentIndex = 0;
	while (currentIndex < countriesRepository->allCountries.size && indexOfTheSearchedCountry == -1)
	{
		if (strstr(getCountryName(&countriesRepository->allCountries.elements[currentIndex]), stringThatIsBeingSearched) != NULL) {
			indexOfTheSearchedCountry = currentIndex;
		}
		currentIndex++;
	}
	return indexOfTheSearchedCountry;
}

/*
  Function that returns the length of the repository
*/
void deleteRepository(Repository* repository)
{
	for (int index = 0; index < repository->allCountries.size; index++)
	{
		destroyCountry(repository->allCountries.elements[index]);
	}
}