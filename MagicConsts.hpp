#pragma once
#ifndef _MY_ILLIGAL_STATE_EXCEPTION_HPP_
#define _MY_ILLIGAL_STATE_EXCEPTION_HPP_


namespace my{
    class MagicConsts{
        private:
            double lowActiveCof;
        public:
            MagicConsts();
            static MagicConsts getDefaulInstance();
            const double getLowActiveCof() const;
    };
}


#endif
