
template<class Integrator>
class DynamicModel : public Integrator {

    public:
        //parameters
        double CutOffFrequency;
      
        //constructor
        DynamicModel () : Integrator (6) {/*empty*/}

        //system of equations
        void ode_fun (double* solin, double* fout) {
            //alias
            double eci_rx   = solin[0];
            double eci_ry   = solin[1];
            double eci_rz   = solin[2];

            //evaluate derivatives
            fout[0] = -1.0/TimeConstant() * Output + 1.0/TimeConstant() * Input;
            fout[1] = 0.0;    
        }
        //jacobian
        void ode_jac (double* solin, double** Jout) {
            //alias
         
            Jout[0][0] = -1.0/TimeConstant();   Jout[0][1] = 1.0/TimeConstant();
            Jout[1][0] =  0.0;                  Jout[1][1] = 0.0;
        }

        void SetInput(double value){
            this->set_sol(1, value);
        }

         double GetInput(){
           return this->get_sol(1);
        }

        void SetOutput(double value){
            this->set_sol(0, value);
        }

        double GetOutput(){
            return this->get_sol(0);
        }

};