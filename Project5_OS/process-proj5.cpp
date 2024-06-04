/* CSI 3334
 * Project 5 -- Real-Time Batch Operating System Simulator
 * Filename: process-proj5.h
 * Student name: Kirby Dyson
 *
 * This file implements the functions from the Process class
 */

#include "process-proj5.h"

/* Process
 *  parameters:
 *      theId -- given ID to set id to
 *  return value:
 *      none
 *
 *  This function is the default constructor.
 */
Process::Process(int theId){
    this->id = theId;
    this->submissionTime = 0;
    this->deadline = 0;
    this->requiredTime = 0;
    this->information = " ";
}

/* run
 *  parameters:
 *      currentSystemTime -- given system time
 *  return value:
 *      system time plus the required time
 *
 *  This function prints out the information contained in this process
 *  and returns the new system time.
 */
int Process::run(int currentSystemTime) const{
    cout << "running process id " << this->id << " at " << currentSystemTime;
    cout << endl;
    cout << this->information << endl;

    return currentSystemTime + this->requiredTime;
}

/* canComplete
 *  parameters:
 *      currentSystemTime -- given system time
 *  return value:
 *      true if the method can be completed, false otherwise
 *
 *  This function returns true if the method would be able to complete
 *  if it starts now, false if it could not finish by its deadline.
 */
bool Process::canComplete(int currentSystemTime) const{
    return currentSystemTime + this->requiredTime <= this->deadline;
}

/* getId
 *  parameters:
 *      none
 *  return value:
 *      id of this Process object
 *
 *  This function returns the id of this Process object.
 */
int Process::getId() const{
    return this->id;
}

/* getSubmissionTime
 *  parameters:
 *      none
 *  return value:
 *      submission time of this Process object
 *
 *  This function returns the submission time of this Process object.
 */
int Process::getSubmissionTime() const{
    return this->submissionTime;
}

/* operator<
 *  parameters:
 *      p -- given Process to compare
 *  return value:
 *      true if (*this) < p, false otherwise.
 *
 *  This function is used to order Processes.
 */
bool Process::operator<(Process const &p) const{
    if(this->deadline < p.deadline){
        return true;
    }
    else if(this->deadline == p.deadline){
        if(this->requiredTime < p.requiredTime){
            return true;
        }
    }
    if(this->deadline == p.deadline and this->requiredTime == p.requiredTime){
        if(this->id < p.id){
            return true;
        }
    }
    return false;
}

/* operator>>
 *  parameters:
 *      is -- given istream to read from
 *      p  -- given Process to read
 *  return value:
 *      information from istream
 *
 *  This function is used to read in the submissionTime, deadline,
 *  requiredTime, and information from an istream.
 */
istream &operator>>(istream &is, Process &p){
    is >> p.submissionTime >> p.deadline >> p.requiredTime;
    getline(is >> ws, p.information);

    return is;
}

