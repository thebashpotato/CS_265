#ifndef GRADER_HPP
#define GRADER_HPP

#include "student.hpp"
#include <vector>

namespace GraderApplication
{
   /* Change template mess, for readabillity */
   using StudentVector = std::vector<StudentData>;

   /* Grader will inherit from both main classes, 
    * utilizing the getters and setters to access, 
    * and manipulate the data to make my life easier.
    *
    * Utilizes the vector of objects approach rather
    * then a map or 2d array
    * */
   class Grader : public Utillity  {
      private:
         int numberOfStudents;
         std::string dataFile;
         StudentVector studentContainer;
      public:
         /* NOTE: Documentation
          * explicit constructor takes in number of students
          * found in from the count routine in main.cpp, and
          * the file name the user supplies
          * */
         Grader(int, const std::string &);

         /* NOTE: Documentation
          * getter for number of students
          * so we can easily reserve space
          * in any temp vectors or arrays we
          * may need
          * */
         int getNumOfStudents(void) const;

         /* NOTE: Documentation
          * getter for the datafile
          * */
         std::string getDataFile() const;

         /* NOTE: Documentation
          * load our vector of student objects
          * */
         void loadVector(void);

         /* NOTE: Documentation
          * the meat of this class, 2 C style for loops.
          * depends on a few helper functions
          * to properly perform computations on the grade data
          * */
         void makeGrades(void);

         /* NOTE: Documentation
          * Helper method of makeGrades, takes in standard i, j
          * C style for loop integers, so it can calculate all grades
          * for each student, against the weight and maxmark
          *
          * Called from within makeGrades inner for loop since it needs
          * to calculate an array being stored in a vector
          * */
         float subGradeComputation(int , int );
         

         /* NOTE: Documentation
          * makes a call to macro routines in settings.h
          * to decide the range of the grade to match it to
          * a lettergrade representation held in the Echelon
          * struct also defined in settings.h
          *
          * called from makeGrades outer forloop
          * */
         std::string assignLetterGrade(float);

         /* NOTE: Documentation
          * Final output method after all grades, are computed,
          * rounded, and stored in StudentContainer Vector
          * */
         void outputFinal(void);

         /* NOTE: Documentation
          * Output all the student error lines that were 
          * perserved allong the way
          * */
         void outputError(void);

         /* NOTE: Documentation
          * Clean up the temp file
          * we have been operating on
          */
         void sanitize(void) const; 
   };
};

#endif