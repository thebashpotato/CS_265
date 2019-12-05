/* All  main documentaion is in header files
 * for corresponding cpp files.
 * */
#include "../hdr/base.h"
#include "../hdr/customExceptions.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>

namespace GraderApplication {
   BaseData::BaseData(void)
      : headerLength(0)
      , totalLineCount(0)
      , title("")
      , titleContainer({""})
      , category("")
      , categoryContainer({""})
      , maxMark("")
      , maxMarkContainer({})
      , weight("")
      , weightContainer({})
   {  }


   int BaseData::getTotalHeaderCount() const { return this->totalHeaderCount; }


   int BaseData::getHeaderLength() const { return this->headerLength; }
   

   void BaseData::setHeaderLength(int _length)
   {
      try {
         if (this->headerLength == 0) {
            /* This is the first time we are setting the data */
            this->headerLength = _length;
         }
         else if (this->headerLength == _length) {
            /* Our lengths match, all is well, do nothing */
         } else {
            /* Our lengths do not match, cannot compute data correctly
             * throw and end program
             * */
            throw DataLength();
         }

      } catch (DataLength &e) {
         std::cerr << e.what() << std::endl;
         exit (EXIT_FAILURE);
      }
   }


   int BaseData::getCurrentLineCount() const { return this->totalLineCount; }


   void BaseData::setCurrentLineCount(int _count)
   {
      /* set an acceptable inclusive bound */
      if (_count >= 0 && _count <= 200) {
         this->totalLineCount += _count;
      } else {
         std::cerr << "File is too large\n"; 
      }
   }


   std::string BaseData::getTitle() const { return this->title; }


   void BaseData::setTitle(const std::string &_title) 
   {
      try {
         if ( this->title.empty() ) { 
            this->title = _title; 
         }
         else {
            throw DuplicateFound();
         }
      } catch (DuplicateFound &e) {
         std::cerr << e.what() << _title << " is already set" << std::endl;
         exit (EXIT_FAILURE);
      }
   }


   std::string BaseData::getTitleContainer(int &itr) const { return this->titleContainer[itr]; }


   void BaseData::setTitleContainer(const std::string &_sub)
   {
      try {
         for (int i = 0; i < this->getHeaderLength(); ++i) {
            if (this->titleContainer[i] == _sub) {
               throw DuplicateFound();
            }
         }
         /* if no exception is thrown insert the value */
         this->titleContainer.push_back(_sub);
      } catch(DuplicateFound &e) {
         std::cerr << e.what() << _sub << " <- already in title container\n";
         exit(EXIT_FAILURE);
      }
   } 


   std::string BaseData::getCategory() const { return this->category; }


   void BaseData::setCategory(const std::string &_category) 
   { 
      try {
         if ( this->category.empty() ) { 
            this->category = _category; 
         }
         else {
            throw DuplicateFound();
         }
      } catch (DuplicateFound &e) {
         std::cerr << e.what() << _category << " is already set" << std::endl;
         exit (EXIT_FAILURE);
      }
   }


   std::string BaseData::getCategoryContainer(int &itr) { return this->categoryContainer[itr]; }


   void BaseData::setCategoryContainer(const std::string &_sub)
   {
      this->categoryContainer.push_back(_sub);
   }


   std::string BaseData::getMaxMark() const { return this->maxMark; }


   void BaseData::setMaxMark(const std::string &_maxMark)
   {
      try {
         if ( this->maxMark.empty() ) { 
            this->maxMark = _maxMark;
         }
         else {
            throw DuplicateFound();
         }
      } catch (DuplicateFound &e) {
         std::cerr << e.what() << _maxMark << " is already set" << std::endl;
         exit (EXIT_FAILURE);
      }
   }


   float BaseData::getMaxMarkContainer(int &itr) { return this->maxMarkContainer[itr]; }


   void BaseData::setMaxMarkContainer(std::string &_sub)
   {
      try {
         if (isDigits(_sub)) {
            float temp = stringTofloat(_sub);
            this->maxMarkContainer.push_back(temp);
         }
         else { throw FailStringFloatConversion(); }

      } catch (FailStringFloatConversion &e) {
         std::cerr << e.what() << _sub << std::endl;
         exit (EXIT_FAILURE);
      }
   }


   std::string BaseData::getWeight() const { return this->weight; }


   void BaseData::setWeight(const std::string &_weight)
   {
      try {
         if ( this->weight.empty() ) { 
            this->weight = _weight;
         }
         else {
            throw DuplicateFound();
         }
      } catch (DuplicateFound &e) {
         std::cerr << e.what() << _weight << " is already set" << std::endl;
         exit (EXIT_FAILURE);
      }
   }


   float BaseData::getWeightContainer(int &itr) { return this->weightContainer[itr]; }


   void BaseData::setWeightContainer(std::string &_sub)
   {
      try {
         if (isDigits(_sub)) {
            float temp = stringTofloat(_sub);
            this->weightContainer.push_back(temp);
         }
         else { throw FailStringFloatConversion(); }

         size_t tempCompare = this->getHeaderLength();
         if (this->weightContainer.size() == tempCompare) {
            // if the container size is equal to the line length
            std::vector<float> Fvec = this->weightContainer;
            float total = vecSummation(Fvec);
            if (total != 100) { 
               throw WeightSummation();
            }
         }
      } catch (FailStringFloatConversion &e) {
         std::cerr << e.what() << _sub << std::endl;
         exit (EXIT_FAILURE);
      } catch (WeightSummation &e) {
         std::cerr << e.what() << std::endl;
         exit (EXIT_FAILURE);
      }
   }


   void BaseData::printBaseObject(void)
   {
      /* get the title */ 
      std::cout << this->getTitle() << " : ";
      for (int i = 0; i < this->getHeaderLength(); ++i) {
         std::cout << this->getTitleContainer(i) << " "; 
      }
      std::cout << std::endl;

      /* get the category */ 
      std::cout << this->getCategory() << " : ";
      for (int i = 0; i < this->getHeaderLength(); ++i) {
         std::cout << this->getCategoryContainer(i) << " "; 
      }
      std::cout << std::endl;

      /* get the maxMark */ 
      std::cout << this->getMaxMark() << " : ";
      for (int i = 0; i < this->getHeaderLength(); ++i) {
         std::cout << this->getMaxMarkContainer(i) << " "; 
      }
      std::cout << std::endl;

      /* get the weight */ 
      std::cout << this->getWeight() << " : ";
      for (int i = 0; i < this->getHeaderLength(); ++i) {
         std::cout << this->getWeightContainer(i) << " "; 
      }
      std::cout << std::endl;
   }


   bool BaseData::loadBaseData(const std::string &file)
   {
      std::ifstream inFile(file);
      std::string line("");
      if (inFile.good()) {
         while (std::getline(inFile, line)) {
            std::string keyword("");
            std::string sTemp("");
            std::stringstream ss(line);
            ss >> keyword;

            if (keyword == TITLE) {
               this->setTitle(keyword);
               for (int i = 0; i < this->getHeaderLength(); ++i) {
                  ss >> sTemp;
                  this->setTitleContainer(sTemp);
               }
            }
            else if (keyword == CATEGORY) {
               this->setCategory(keyword);
               for (int i = 0; i < this->getHeaderLength(); ++i) {
                  ss >> sTemp;
                  this->setCategoryContainer(sTemp);
               }
            }
            else if (keyword == MAXMARK) {
               this->setMaxMark(keyword);
               for (int i = 0; i < this->getHeaderLength(); ++i) {
                  ss >> sTemp;
                  this->setMaxMarkContainer(sTemp);
               }
            }
            else if (keyword == WEIGHT) {
               this->setWeight(keyword);
               for (int i = 0; i < this->getHeaderLength(); ++i) {
                  ss >> sTemp;
                  this->setWeightContainer(sTemp);
               }
            }
         }
      }
      inFile.close();
      return true;
   }
   

   void BaseData::stripComments(std::string &line)
   {
      std::size_t found = line.find(COMM);
      if (found != std::string::npos) {
         line.erase(found, std::string::npos);
      } else {
         std::cerr << "No comment found in this line" << std::endl;
      }
   }


   int BaseData::findEvaluationLenth(std::string &datafile)
   {
      datafile = "";
      return 1;
   }


   bool BaseData::isDigits(std::string &s)
   {
     return s.find_first_not_of("0123456789.") == std::string::npos; 
   }


   float BaseData::stringTofloat(const std::string &s)
   {
      float tempconvert = 0;
      std::stringstream streamVar(s);
      try {
         streamVar >> tempconvert;
         if (streamVar.fail()) {
            throw StreamConversionFailure();
         }
      } catch (StreamConversionFailure &e) {
         std::cerr << e.what() << &streamVar << std::endl;
         exit (EXIT_FAILURE);
      }
      // will only return upon success
      return tempconvert;
   }


   float BaseData::vecSummation(std::vector<float> &s)
   {
      float tempFinalGrade = 0;
      return accumulate(s.begin(), s.end(), tempFinalGrade);
   }
};
