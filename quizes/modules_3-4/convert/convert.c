unsigned int convert(unsigned int n)
{
    if(n < 2552){
        return 800;
    }
    unsigned int denominator = n - 1058;
    return 1195172 / denominator;
}

int main()
{
    unsigned int sensor_reading = 2552;
    unsigned int converted_reading = convert(sensor_reading);

    return 0;
}
