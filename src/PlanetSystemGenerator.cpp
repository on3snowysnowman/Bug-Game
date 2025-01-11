/**
 * @file PlanetSystemGenerator.cpp
 * @author Joel Height (On3SnowySnowman@gmail.com)
 * @brief Single class implementation.
 * @version 0.1
 * @date 01-10-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <Fr_WeightedDistribution.hpp>

#include "PlanetSystemGenerator.hpp"
#include "NameGenerators.hpp"


// Public

std::vector<Planet> PlanetSystemGenerator::generate_planet_system(GameDifficulty game_difficulty)
{
    static WeightedDistribution<PLANET_TYPE, 12> planet_type_options
    (
        {ICY_DWARF, ROCKY_DWARF, METALLIC_DWARF, ARCTIC_WORLD, DESERT_WORLD, 
        TERRESTRIAL_PLANET, ROCKY_PLANET, LAVA_WORLD, ICE_GIANT, SUPER_EARTH, 
        GAS_GIANT, DENSE_GAS_GIANT}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    );

    uint8_t num_planets;

    std::vector<Planet> planets;

    // Handle the game difficulty, which specifies the types of planets that can be generated along
    // with the number of planets.
    switch(game_difficulty)
    {
        case ROUTINE_OPERATION: 

            planet_type_options.set_values()
            num_planets = FrostRandom::get_random_int(3, 4);
            break;

        case LOW_RESISTANCE:

            num_planets = FrostRandom::get_random_int(4, 5);
            break;

        case STANDARD_PROTOCOL:

            num_planets = FrostRandom::get_random_int(4, 6);
            break;

        case UNYIELDING_FRONTLINES:

            num_planets = FrostRandom::get_random_int(5, 7);
            break;

        case THEN_THERE_WERE_BUGS:

            num_planets = FrostRandom::get_random_int(6, 8);
            break;
    }

    // Generate the planets of the system.
    for(uint8_t i = 0; i < num_planets; ++i)
    {
        // Sample from the planet type options, configured by the difficulty previously.
        switch(planet_type_options.sample())
        {
            case ICY_DWARF:

                planets.push_back(_generate_icy_dwarf());                
                continue;
            
            case ROCKY_DWARF:
                
                planets.push_back(_generate_rocky_dwarf());
                continue;
            
            case METALLIC_DWARF:
                
                planets.push_back(_generate_metallic_dwarf());
                continue;
            
            case ARCTIC_WORLD:
                
                planets.push_back(_generate_arctic_world());
                continue;
            
            case DESERT_WORLD:
                
                planets.push_back(_generate_desert_world());
                continue;
            
            case TERRESTRIAL_PLANET:
                
                planets.push_back(_generate_terrestrial_planet());
                continue;
            
            case ROCKY_PLANET:
               
                planets.push_back(_generate_rocky_planet());
                continue;
            
            case LAVA_WORLD:
                
                planets.push_back(_generate_lava_world());
                continue;
            
            case ICE_GIANT:
                
                planets.push_back(_generate_ice_giant());
                continue;
            
            case SUPER_EARTH:
                planets.push_back(_generate_super_earth());
                continue;
            
            case GAS_GIANT:
               
                planets.push_back(_generate_gas_giant());
                continue;
            
            case DENSE_GAS_GIANT:
               
                planets.push_back(_generate_dense_gas_giant());
                continue;
        }
    }
    
    return planets;
}



// Private


Planet PlanetSystemGenerator::_generate_icy_dwarf() 
{
    Planet planet;

    planet.planet_type = ICY_DWARF;

    planet.size = FrostRandom::get_random_int(3, 7);
    planet.distance_from_star = FrostRandom::get_random_int(15, 25);

    planet.name = NameGenerators::generate_planet_name();
    planet.planet_type_readable = "Icy Dwarf";

    return planet;
}

Planet PlanetSystemGenerator::_generate_rocky_dwarf() 
{
    Planet planet;

    planet.planet_type = ROCKY_DWARF;

    planet.size = FrostRandom::get_random_int(4, 8);
    planet.distance_from_star = FrostRandom::get_random_int(9, 15);

    planet.name = NameGenerators::generate_planet_name();
    planet.planet_type_readable = "Rocky Dwarf";

    return planet;
}

Planet PlanetSystemGenerator::_generate_metallic_dwarf() 
{
    Planet planet;

    planet.planet_type = METALLIC_DWARF;

    planet.size = FrostRandom::get_random_int(3, 6);
    planet.distance_from_star = FrostRandom::get_random_int(5, 8);

    planet.name = NameGenerators::generate_planet_name();
    planet.planet_type_readable = "Metallic Dwarf";

    return planet;
}

Planet PlanetSystemGenerator::_generate_arctic_world() 
{
    Planet planet;

    planet.planet_type = ARCTIC_WORLD;

    planet.size = FrostRandom::get_random_int(15, 20);
    planet.distance_from_star = FrostRandom::get_random_int(15, 25);

    planet.name = NameGenerators::generate_planet_name();
    planet.planet_type_readable = "Arctic World";

    return planet;
}

Planet PlanetSystemGenerator::_generate_desert_world() 
{
    Planet planet;

    planet.planet_type = DESERT_WORLD;

    planet.size = FrostRandom::get_random_int(15, 20);
    planet.distance_from_star = FrostRandom::get_random_int(6, 10);

    planet.name = NameGenerators::generate_planet_name();
    planet.planet_type_readable = "Desert World";

    return planet;
}

Planet PlanetSystemGenerator::_generate_terrestrial_planet() 
{
    Planet planet;

    planet.planet_type = TERRESTRIAL_PLANET;

    planet.size = FrostRandom::get_random_int(12, 16);
    planet.distance_from_star = FrostRandom::get_random_int(12, 15);

    planet.name = NameGenerators::generate_planet_name();
    planet.planet_type_readable = "Terrestrial Planet";

    return planet;
}

Planet PlanetSystemGenerator::_generate_rocky_planet() 
{
    Planet planet;

    planet.planet_type = ROCKY_PLANET;

    planet.size = FrostRandom::get_random_int(12, 20);
    planet.distance_from_star = FrostRandom::get_random_int(9, 15);

    planet.name = NameGenerators::generate_planet_name();
    planet.planet_type_readable = "Rocky Planet";

    return planet;
}

Planet PlanetSystemGenerator::_generate_lava_world() 
{
    Planet planet;

    planet.planet_type = LAVA_WORLD;

    planet.size = FrostRandom::get_random_int(12, 16);
    planet.distance_from_star = FrostRandom::get_random_int(3, 5);

    planet.name = NameGenerators::generate_planet_name();
    planet.planet_type_readable = "Lava World";

    return planet;
}

Planet PlanetSystemGenerator::_generate_ice_giant() 
{
    Planet planet;

    planet.planet_type = ICE_GIANT;

    planet.size = FrostRandom::get_random_int(25, 32);
    planet.distance_from_star = FrostRandom::get_random_int(30, 40);

    planet.name = NameGenerators::generate_planet_name();
    planet.planet_type_readable = "Ice Giant";

    return planet;
}

Planet PlanetSystemGenerator::_generate_super_earth() 
{
    Planet planet;

    planet.planet_type = SUPER_EARTH;

    planet.size = FrostRandom::get_random_int(20, 30);
    planet.distance_from_star = FrostRandom::get_random_int(10, 15);

    planet.name = NameGenerators::generate_planet_name();
    planet.planet_type_readable = "Super Earth";

    return planet;
}

Planet PlanetSystemGenerator::_generate_gas_giant() 
{
    Planet planet;

    planet.planet_type = GAS_GIANT;

    planet.size = FrostRandom::get_random_int(25, 32);
    planet.distance_from_star = FrostRandom::get_random_int(25, 25);

    planet.name = NameGenerators::generate_planet_name();
    planet.planet_type_readable = "Gas Giant";

    return planet;
}

Planet PlanetSystemGenerator::_generate_dense_gas_giant() 
{
    Planet planet;

    planet.planet_type = DENSE_GAS_GIANT;

    planet.size = FrostRandom::get_random_int(1, 4);
    planet.distance_from_star = FrostRandom::get_random_int(8, 20);

    planet.name = NameGenerators::generate_planet_name();
    planet.planet_type_readable = "Dense Gas Giant";

    return planet;
}
