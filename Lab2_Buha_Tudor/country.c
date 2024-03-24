#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "country.h"

/*
  Function that creates a new country
*/
Country createNewCountry(char nameOfTheCountry[], char continentOfTheCountry[], long int populationOfTheCountry)
{
	Country newCountry;

	newCountry.name = malloc((strlen(nameOfTheCountry) + 1) * sizeof(char));
	if (newCountry.name == NULL)
		return newCountry;
	strcpy(newCountry.name, nameOfTheCountry);

	newCountry.continent = malloc((strlen(continentOfTheCountry) + 1) * sizeof(char));
	if (newCountry.continent == NULL)
	{
		free(newCountry.name);
		return newCountry;
	}
	strcpy(newCountry.continent, continentOfTheCountry);

	newCountry.population = populationOfTheCountry;

	return newCountry;
}
/*
  Function that returns the name of a country

*/
char* getCountryName(Country* country)
{
	return country->name;
}

/*
  Function that returns the continent of a country
*/
char* getCountryContinent(Country* country)
{
	return country->continent;
}

/*
  Function that returns the population of a country
*/
long int getCountryPopulation(Country* country)
{
	return country->population;
}

/*
  Function that sets the name of a country
*/
void turnCountryToString(Country country, char* countryString[])
{
	sprintf(countryString, "The country %s is from %s and has a population of %ld citizens.", country.name, country.continent, country.population);
}

/*
  Function that sets the name of a country
*/
void destroyCountry(Country countryToDestroy)
{
	free(countryToDestroy.name);
	free(countryToDestroy.continent);
}