#include "cmd_options.h"
#include <gtest/gtest.h>
namespace ProgramOptions
{
    TEST(ProgramOptions, TestName){


        EXPECT_NO_THROW({
            CryptoGuard::ProgramOptions programOpt;
            char *argv = "help 123";
            programOpt.Parse(2,&argv);
        });
    }

    TEST(ProgramOptions, TestName2){ 
        
        
        EXPECT_NO_THROW({
            CryptoGuard::ProgramOptions programOpt;
            char *argv = "command 123";
            programOpt.Parse(2,&argv);
        });
    }
    
    TEST(ProgramOptions, TestName3){ 
        
        
        EXPECT_THROW({
            CryptoGuard::ProgramOptions programOpt;
            char *argv = "help 123";
            programOpt.Parse(6,&argv);
        },std::logic_error);
    }

    TEST(ProgramOptions, TestName4){ 
        
        
        EXPECT_THROW({
            CryptoGuard::ProgramOptions programOpt;
            char *argv = "help 123";
            programOpt.Parse(6,&argv);
        },std::logic_error);
    }


}