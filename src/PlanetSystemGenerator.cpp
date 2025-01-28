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


// Static Members

WeightedDistribution<PLANET_TYPE, NUM_PLANET_TYPES> PlanetSystemGenerator::s_planet_type_options
(
    {ICY_DWARF, ROCKY_DWARF, METALLIC_DWARF, ARCTIC_WORLD, DESERT_WORLD, 
    TERRESTRIAL_PLANET, ROCKY_PLANET, LAVA_WORLD, ICE_GIANT, SUPER_EARTH, 
    GAS_GIANT, DENSE_GAS_GIANT}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
);

uint8_t PlanetSystemGenerator::s_minimum_planets_per_generation {};
uint8_t PlanetSystemGenerator::s_maximum_planets_per_generation {};


// Public

void PlanetSystemGenerator::set_planet_generation_weights(
    const json& planet_generation_weights_json) 
{ 
    if(planet_generation_weights_json.size() < NUM_PLANET_TYPES)
    {
        TextFileHandler::add_to_buffer("[ERR] PlanetSystemGenerator::set_planet_generation_weight"
        "s(const json& planet_generation_weights_json) -> Attempted to set weights with an "
        "insufficient size json array.");
        TextFileHandler::write("CrashLog.txt", Frost::APPEND);
        exit(0);
    }       

    std::array<uint32_t, NUM_PLANET_TYPES> planet_generation_weights;

    for(uint8_t i = 0; i < NUM_PLANET_TYPES; ++i)
    {
        planet_generation_weights.at(i) = planet_generation_weights_json.at(i).at(1);
    }

    s_planet_type_options.set_weights<std::array<uint32_t, NUM_PLANET_TYPES>>
        (planet_generation_weights);
}

void PlanetSystemGenerator::set_minimum_planets_per_generation(uint8_t minimum) 
{ s_minimum_planets_per_generation = minimum; }

void PlanetSystemGenerator::set_maximum_planets_per_generation(uint8_t maximum) 
{ s_maximum_planets_per_generation = maximum; }

std::vector<Planet> PlanetSystemGenerator::generate_planet_system()
{
    // Generate a random number of planets.
    uint8_t num_planets = FrostRandom::get_random_num<uint8_t>(s_minimum_planets_per_generation,
        s_maximum_planets_per_generation);

    // Get the weights of the planets before they are modified by this function.
    const std::array<uint32_t, NUM_PLANET_TYPES> initial_weights = 
        s_planet_type_options.get_weights();

    // Planets that are generated.
    std::vector<Planet> planets;

    // Generate the planets of the system.
    for(uint8_t i = 0; i < num_planets; ++i)
    {
        // Sample a planet type to generate.
        PLANET_TYPE sample = s_planet_type_options.sample();

        // Get the weight of the planet type that was sampled.
        const uint32_t& EXISTING_WEIGHT = s_planet_type_options.get_weights().at(sample);

        // Multiply the weight of this planet type by 80%, to make it less likely of showing up 
        // again.
        s_planet_type_options.set_weight(sample, EXISTING_WEIGHT * 0.8);

        // Sample from the planet type options, configured by the difficulty previously.
        // switch(s_planet_type_options.sample())
        switch(sample)
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

    // Reset the weights to their initial values.
    s_planet_type_options.set_weights(initial_weights);

    return planets;
}



// Private


Planet PlanetSystemGenerator::_generate_icy_dwarf() 
{
    Planet planet;

    planet.planet_type = ICY_DWARF;

    planet.size = FrostRandom::get_random_num<uint8_t>(3, 7);
    planet.distance_from_star = FrostRandom::get_random_num<uint8_t>(15, 25);

    planet.name = NameGenerators::generate_planet_name();

    return planet;
}

Planet PlanetSystemGenerator::_generate_rocky_dwarf() 
{
    Planet planet;

    planet.planet_type = ROCKY_DWARF;

    planet.size = FrostRandom::get_random_num<uint8_t>(4, 8);
    planet.distance_from_star = FrostRandom::get_random_num<uint8_t>(9, 15);

    planet.name = NameGenerators::generate_planet_name();

    return planet;
}

Planet PlanetSystemGenerator::_generate_metallic_dwarf() 
{
    Planet planet;

    planet.planet_type = METALLIC_DWARF;

    planet.size = FrostRandom::get_random_num<uint8_t>(3, 6);
    planet.distance_from_star = FrostRandom::get_random_num<uint8_t>(5, 8);

    planet.name = NameGenerators::generate_planet_name();
    return planet;
}

Planet PlanetSystemGenerator::_generate_arctic_world() 
{
    Planet planet;

    planet.planet_type = ARCTIC_WORLD;

    planet.size = FrostRandom::get_random_num<uint8_t>(15, 20);
    planet.distance_from_star = FrostRandom::get_random_num<uint8_t>(15, 25);

    planet.name = NameGenerators::generate_planet_name();
    return planet;
}

Planet PlanetSystemGenerator::_generate_desert_world() 
{
    Planet planet;

    planet.planet_type = DESERT_WORLD;

    planet.size = FrostRandom::get_random_num<uint8_t>(15, 20);
    planet.distance_from_star = FrostRandom::get_random_num<uint8_t>(6, 10);

    planet.name = NameGenerators::generate_planet_name();

    return planet;
}

Planet PlanetSystemGenerator::_generate_terrestrial_planet() 
{
    Planet planet;

    planet.planet_type = TERRESTRIAL_PLANET;

    planet.size = FrostRandom::get_random_num<uint8_t>(12, 16);
    planet.distance_from_star = FrostRandom::get_random_num<uint8_t>(12, 15);

    planet.name = NameGenerators::generate_planet_name();

    return planet;
}

Planet PlanetSystemGenerator::_generate_rocky_planet() 
{
    Planet planet;

    planet.planet_type = ROCKY_PLANET;

    planet.size = FrostRandom::get_random_num<uint8_t>(12, 20);
    planet.distance_from_star = FrostRandom::get_random_num<uint8_t>(9, 15);

    planet.name = NameGenerators::generate_planet_name();

    return planet;
}

Planet PlanetSystemGenerator::_generate_lava_world() 
{
    Planet planet;

    planet.planet_type = LAVA_WORLD;

    planet.size = FrostRandom::get_random_num<uint8_t>(12, 16);
    planet.distance_from_star = FrostRandom::get_random_num<uint8_t>(3, 5);

    planet.name = NameGenerators::generate_planet_name();
    return planet;
}

Planet PlanetSystemGenerator::_generate_ice_giant() 
{
    Planet planet;

    planet.planet_type = ICE_GIANT;

    planet.size = FrostRandom::get_random_num<uint8_t>(25, 32);
    planet.distance_from_star = FrostRandom::get_random_num<uint8_t>(30, 40);

    planet.name = NameGenerators::generate_planet_name();
    return planet;
}

Planet PlanetSystemGenerator::_generate_super_earth() 
{
    Planet planet;

    planet.planet_type = SUPER_EARTH;

    planet.size = FrostRandom::get_random_num<uint8_t>(20, 30);
    planet.distance_from_star = FrostRandom::get_random_num<uint8_t>(10, 15);

    planet.name = NameGenerators::generate_planet_name();
    return planet;
}

Planet PlanetSystemGenerator::_generate_gas_giant() 
{
    Planet planet;

    planet.planet_type = GAS_GIANT;

    planet.size = FrostRandom::get_random_num<uint8_t>(25, 32);
    planet.distance_from_star = FrostRandom::get_random_num<uint8_t>(25, 25);

    planet.name = NameGenerators::generate_planet_name();
    return planet;
}

Planet PlanetSystemGenerator::_generate_dense_gas_giant() 
{
    Planet planet;

    planet.planet_type = DENSE_GAS_GIANT;

    planet.size = FrostRandom::get_random_num<uint8_t>(18, 24);
    planet.distance_from_star = FrostRandom::get_random_num<uint8_t>(8, 20);

    planet.name = NameGenerators::generate_planet_name();
    return planet;
}
