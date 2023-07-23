#include "./include/global.hpp"

long getContextNextID()
{
    hmc_Object_Context_id++;
    return hmc_Object_Context_id;
};

long hmc_Object_Context_id = 0;

bool newHMC()
{
    return true;
}