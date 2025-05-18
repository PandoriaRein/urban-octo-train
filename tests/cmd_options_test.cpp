#include "cmd_options.h"
#include <gtest/gtest.h>
namespace ProgramOptions
{
    TEST(ProgramOptions, TestName){


        EXPECT_NO_THROW({
            CryptoGuard::ProgramOptions programOpt;
            char *argv = "help1 123";
            programOpt.Parse(2,&argv);
        });
    }

    TEST(ProgramOptions, TestName2){ 
        
        
        EXPECT_NO_THROW({
            CryptoGuard::ProgramOptions programOpt;
            char *argv = "help1 123";
            programOpt.Parse(2,&argv);
        });
    }//по какой-то причине тесты не запускаются
    


}