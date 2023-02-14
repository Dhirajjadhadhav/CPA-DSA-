unsigned long hash_long(unsigned long val, unsigned int bits)
{
    unsigned long hash = val * 0x9e370001UL;
    return (hash) >> (32-bits);
}

void test(unsigned long val, unsigned long nr_bucket_power)
{
    hash_long(val, nr_bucket_power);        // nr_buckeds must be in the power of two;
}

nr_bucket_power = (unsigned long )log(nr_buckets, 2);

floor(long(nr_bucket, 2));

//Exerscise:
//Make change into hash queue code to incorparate 
// adv hash function 
