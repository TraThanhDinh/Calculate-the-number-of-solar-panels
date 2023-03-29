#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <sstream>


using namespace std;

int main() {

    // constant definitions

    const string LINE =
        "---------------------------------------------------------------------";
    const int    SOLAR_IRRADIANCE = 1000; // origanal solar irradiance
    const double PANEL_WIDTH      = 1.0;     // origanal width meters
    const double PANEL_LENGTH     = 1.6;     // origanal length meters
    const double METER_TO_FEET    = 3.280839895013123 * 3.280839895013123;
                                    // meter to feet

    // variable declarations
    ifstream   infile;          // to openfile

    double     latitude;        // in put the lattude
    int        roof_direction;  // input the roof deirection
    double     sunlight_hours;  // sun light hours 3 to 6 hours
    double     annual_power;    // the annuall power

    double     latitude_efficiency;
    double     lat_min_1;               // the minumun lat 25
    double     lat_max_1;               // the maxinum lat 35
    double     lat_eff_1;               // the effeciency lat

    double     lat_min_2;               // the minumun lat 35
    double     lat_max_2;               // the maxinum lat 45
    double     lat_eff_2;               // the effeciency lat

    double     lat_min_3;               // the minumun lat 45
    double     lat_max_3;               // the maxinum lat 55
    double     lat_eff_3;               // the effeciency lat

    double     roof_1;                  // the roof direction 360
    double     panel_eff_1;             // the panel efficiency
    double     roof_2;                  // the roof direction 90
    double     panel_eff_2;             // the panel efficiency
    double     roof_3;                  // the roof direction 180
    double     panel_eff_3;             // the panel efficiency
    double     roof_4;                  // the roof direction 270
    double     panel_eff_4;             // the panel efficiency
    double     panel_efficiency;        // the real panel efficiency


    double     combined_efficiency;     // the combined efficiency
    double     power_per_square_meter;  // power per square meter
    double     panel_power;             // panel power
    double     total_daily_panel_power; // total daily panel power
    double     panel_size;              // panel size length and width
    double     total_annual_panel_power;// total annual panel power
    double     panels_required;         // panels reqired to make
    double     roof_area_required;      // the acually area of panel
    int        exit_status = 0;         // the exit fail
    string     direction;               // name for direction E, S, W, N.


    // input the latitude, roof direction, sunlight hours, annual power.
    cin >> latitude
        >> roof_direction
        >> sunlight_hours
        >> annual_power;

    // Read in efficiency data from file
    infile.open("solar_eff_data.dat");
    infile.ignore(100, '\n');

    // read if lattitude

    infile >> lat_min_1;
    infile.ignore();
    infile >> lat_max_1;
    infile.ignore(2, '\n');
    infile >> lat_eff_1;

    infile >> lat_min_2;
    infile.ignore();
    infile >> lat_max_2;
    infile.ignore(2, '\n');
    infile >> lat_eff_2;

    infile >> lat_min_3;
    infile.ignore();
    infile >> lat_max_3;
    infile.ignore(2, '\n');
    infile >> lat_eff_3;

    if (lat_min_1 <= latitude && latitude < lat_max_1) {
        latitude_efficiency = lat_eff_1;
    } else if (lat_min_2 <= latitude && latitude < lat_max_2) {
        latitude_efficiency = lat_eff_2;
    } else if (lat_min_3 <= latitude && latitude < lat_max_3) {
        latitude_efficiency = lat_eff_3;
    }

    // reaf the roof direction

    infile.ignore(100, '#');
    infile.ignore(100, '\n');

    infile >> roof_1;
    infile.ignore();
    infile >> panel_eff_1;
    infile.ignore(2, '\n');

    infile >> roof_2;
    infile.ignore();
    infile >> panel_eff_2;
    infile.ignore(2, '\n');

    infile >> roof_3;
    infile.ignore();
    infile >> panel_eff_3;
    infile.ignore(2, '\n');

    infile >> roof_4;
    infile.ignore();
    infile >> panel_eff_4;
    infile.ignore(2, '\n');

    if (roof_1 == roof_direction) {
        panel_efficiency = panel_eff_1;
    } else if (roof_2 == roof_direction) {
        panel_efficiency = panel_eff_2;
    } else if (roof_3 == roof_direction) {
        panel_efficiency = panel_eff_3;
    } else if (roof_4 == roof_direction) {
        panel_efficiency = panel_eff_4;
    }

    infile.close();

    // check if input wrong( not the number)
    if (!cin) {
        cout << "Input stream failure detected.\n"
                "Check: Latitude, Roof direction, Solar Hours, "
                "Total annual power usage"
             << endl;
        return 1;
    }


    // check if input sunlight hours from 3 to 6, output wrong if it less than
    // 3 and more than 6
    if (sunlight_hours < 3 || sunlight_hours > 6) {
        cout << "Invalid entry: Sunlight hours outside the"
                " range of 3 - 6 hrs/day."
             << endl;
        return 1;
        }
    // check if the input latitude not from 25 to 55
    if (latitude < lat_min_1 || latitude > lat_max_3) {
        cout << "Invalid entry: Latitude input is outside the data set range."
             << endl;
        cout << "Enter a latitude within the range 25 - 55 degrees." << endl;
        return 1;
    }

    // use the switch statment to chech number 90, 180, 270, and 360
    switch (roof_direction) {
        case 360:
            direction ="North";
            break;
        case 90:
            direction = "Eest";
            break;
        case 180:
            direction = "South";
            break;
        case 270:
            direction = "West";
            break;
        default:
            cerr << "Invalid entry: Roof facing direction.\n"
                    "Make sure to only enter 360, 90, 180 or 270.";
            return 1;
        }
    // Calculate power output per square meter of solar cells
    combined_efficiency      = (latitude_efficiency + panel_efficiency) / 2;
    power_per_square_meter   = SOLAR_IRRADIANCE * combined_efficiency;

    // Calculate power output for panel
    panel_size               = PANEL_WIDTH * PANEL_LENGTH;
    panel_power              = power_per_square_meter * panel_size;

    // Calculate daily power output for panel
    total_daily_panel_power  = panel_power * sunlight_hours;

    // Calculate number of panels and roof area required
    total_annual_panel_power = total_daily_panel_power * 365;
    panels_required          = ceil(annual_power * 1000 /
                               total_annual_panel_power);
    roof_area_required       = panels_required * panel_size * METER_TO_FEET;

    // output

    cout << "Solar Panel Installation Report" << endl;
    cout << LINE << endl;
    cout << left << setw(17) << "Latitude" << setw(17) << "Direction"
         << setw(17) << "Daily Solar Hrs" << right << setw(10)
         << "Annual Power Used" << endl;
    cout << LINE << endl;
    cout << left << setw(17) << fixed << setprecision(4) << latitude
         << setw(17) << direction << setw(17) << fixed
         << setprecision(1) << sunlight_hours << fixed << setprecision(2)
         << right << setw(13) << annual_power << " kWh" << endl;

    cout << "\nSingle panel output for this location: " << fixed << showpoint
         << setprecision(2) << panel_power << " WattS" << endl;
    cout << "Total number of required panels: "<< fixed << setprecision(0)
         << static_cast<int> (panels_required) << endl;
    cout << "Required roof area: " << fixed << showpoint << setprecision(2)
         << roof_area_required << " Square Feet" << endl;

    return exit_status;
}
