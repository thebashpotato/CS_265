#ifndef STUDENT_H
#define STUDENT_H

#include "base.h"
#include "settings.h"
#include <vector>

namespace GraderApplication {
   /* For every occurance of a valid student line
    * in the given file a student object will be created
    * and stored in a corresponding vector of the same type
    * defined and handled from the grader class. 
    *
    * This class is equiped with the proper getters and setters
    * so all private data can easily be accessed and manipulated
    * from inheriting classes.
    * */ 
   class StudentData : public BaseData {
      private:
         std::string name;
         std::vector <float> gradesContainer;
         float finalGrade;
         std::string letterGrade;
         bool isWDR;

      public:
         /* XXX: Documentation
          * default constructor
          * */
         StudentData(void);

         /* XXX: Documentation
          * error print will in all output from 
         */
         virtual void errorPrint (const char *);


         /* XXX: Documentation
          * getters and setters for name
          * TODO: rename to studentId
          * */
         std::string getName() const;
         void setName(std::string &);

         /* XXX: Documentation
          * getters and setters for grades container
          * */
         float getGrades(int &);
         void setGrades(std::string &);

         /* XXX: Documentation
          * getter and setter for the final grade
          * obtained by the student
          * */
         float getFinalGrade() const;
         void setFinalGrade(const float &);
         
         /* XXX: Documentation
          * getters and setters for the Letter
          * grader obtained by the student
          * */
         std::string getLetterGrade() const;
         void setLetterGrade(const std::string &);

         /* XXX: Documentation
          * getters and setters to switch 
          * WDR to true
          * */
         bool getIsStudentWDR() const;
         void setIsStudentWDR(bool);

         /* XXX: Documentation
          * A debug and testing method, prints a
          * raw student object, meant to be used by
          * a ranged for loop
          * */
         void printStudentObject();

         /* XXX: Documentation
          * Deletes the temp.txt file created
          * after all data is read in, currently
          * uses std::system to spawn a new shell
          * and run the rm command. Quick way for now
          * TODO: Learn how to delete files using only C++
          * */
         void sanitize(void) const;

         /* XXX: Documentation
          * Main method for Student Class, it uses the
          * file position set from BaseHeader class, 
          * to skip right to where the students section is.
          *
          * The method its self is very similar to how loadBaseData
          * works in the BaseHeader Class
          * */
         bool loadStudentFile(const std::string &);

         /* XXX: Documentation
          * Overloaded method to search for just one stutent and 
          * compute the grade if the -s flag is given
          * */
         bool loadStudentFile(const std::string &, const std::string &);

         /* XXX: Documentation
          * Helper method for loadDataFile, checks if student is found
          * in temp file by string comparison, returns true or false
          * */
         bool isStudentProcessed(const std::string &);


         /* XXX: Documentation
          * first test for tempfile existance, if it doesnt we havnt
          * read the file at all yet
          * */
         bool testForFileExistance(const std::string &);

         /* XXX: Documentation
          * after a student is read in to the studentvector, this
          * method writes said processed student to the temp file
          * then closes it, if the file doesnt exist yet it creates it.
          * it is careful to append students, and not trample previously
          * written data.
          * */
         void processStudent(const std::string &);

         /* XXX: Documentation
          * check if string is only alpha numeric
          * */
         bool isAlphaNumeric(std::string &);
         
         /* XXX: Documentation
          * Convert a string to upper case 
          * using transform, code comes from 
          * cpp preference transform Documentation
          */
         std::string convert_toupper(std::string);
   };
};
#endif
