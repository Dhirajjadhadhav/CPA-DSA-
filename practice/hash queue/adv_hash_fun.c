unsigned long hash_long(unsigned long val, unsigned int bits)
{
    unsigned long hash =  val * 0x9e370001UL;
    return hash>>(32-bits); 
}

void test(unsigned long val, unsigned long nr_buckets_power)
{
    hash_long(val, nr_buckets_power);   //nr_bucket must be in the power of two
}

nr_buckets_power = (unsigned long)log(nr_buckets, 2);

floor(log(nr_buckets, 2));

//EXERCISE:
//Make changes into hash queue code to incarporate
// adv hash function discuss above 

