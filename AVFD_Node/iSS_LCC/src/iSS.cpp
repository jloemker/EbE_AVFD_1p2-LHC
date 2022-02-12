
#include <memory>

#include "Table.h"
#include "arsenal.h"
#include "iSS.h"
#include "Random.h"


using namespace std;

iSS::iSS(string path_in) {
    path = path_in;
    flag_PCE = 0;

    efa = nullptr;
    paraRdr_ptr = new ParameterReader;
}

iSS::~iSS() {
    FOsurf_ptr.clear();
    particle.clear();
    if (efa != nullptr) {
        delete efa;
    }
}

int iSS::shell() {
    int status = read_in_FO_surface();
    if (status != 0) {
        cout << "Some errors happened in reading in the hyper-surface" << endl;
        exit(-1);
    }
    set_random_seed();
    status = generate_samples();
    if (status != 0) {
        cout << "Some errors happened in generating particle samples" << endl;
        exit(-1);
    }
    return(0);
}

int iSS::read_in_FO_surface() {
    read_FOdata freeze_out_data(paraRdr_ptr, path);
    freeze_out_data.read_in_freeze_out_data(FOsurf_ptr);
    cout << "total number of cells: " <<  FOsurf_ptr.size() << endl;
    freeze_out_data.read_in_chemical_potentials(path, FOsurf_ptr, particle);
    flag_PCE = freeze_out_data.get_flag_PCE();
    cout << endl << " -- Read in data finished!" << endl << endl;
    return(0);
}


void iSS::set_random_seed() {
    randomSeed  = paraRdr_ptr->getVal("randomSeed");
    ran_gen_ptr = std::shared_ptr<RandomUtil::Random>(
                                        new RandomUtil::Random(randomSeed));
}


void iSS::set_random_seed(int randomSeed_in) {
    randomSeed = randomSeed_in;
    ran_gen_ptr = std::shared_ptr<RandomUtil::Random>(
                                        new RandomUtil::Random(randomSeed));
}

int iSS::generate_samples() {
    // skip others except for these particle
    Table chosen_particles(table_path + "/chosen_particles.dat");

    Table pT_tab(table_path + "/bin_tables/pT_gauss_table.dat");
    Table phi_tab(table_path + "/bin_tables/phi_gauss_table.dat");
    // eta uniform dist table
    Table eta_tab(table_path + "/bin_tables/eta_uni_table.dat");
    // Table eta_tab("tables/eta_gauss_table_30_full.dat");

    efa = new EmissionFunctionArray(ran_gen_ptr,
            &chosen_particles, &pT_tab, &phi_tab, &eta_tab,
            particle, FOsurf_ptr, flag_PCE, paraRdr_ptr, path);
    efa->shell();

    return(0);
}

