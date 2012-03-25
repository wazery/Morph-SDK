#include "mattribute.h"

using namespace Morph;

bool MAttribute::setValueByString(const MString &valueStr)
{
    return _setValueByString(mValue, valueStr);
}

bool MAttribute::_setValueByString(boost::any &dstValue, const MString &valueStr)
{
    try
    {
        if (dstValue.empty())
            return false;

        string valueString = valueStr.toUtf8().constData();

        if(dstValue.type() == typeid(int))
        {
            int v = boost::lexical_cast<int>(valueString);
            dstValue = v;
        }
        else if(dstValue.type() == typeid(unsigned int))
        {
            unsigned int v = boost::lexical_cast<unsigned int>(valueString);
            dstValue = v;
        }
        else if(dstValue.type() == typeid(long))
        {
            long v = boost::lexical_cast<long>(valueString);
            dstValue = v;
        }
        else if(dstValue.type() == typeid(unsigned long))
        {
            unsigned long v = boost::lexical_cast<unsigned long>(valueString);
            dstValue = v;
        }
        else if(dstValue.type() == typeid(float))
        {
            float v = boost::lexical_cast<float>(valueString);
            dstValue = v;
        }
        else if(dstValue.type() == typeid(MDegreeAngle))
        {
            MReal v = boost::lexical_cast<MReal>(valueString);
            dstValue = MDegreeAngle(v);
        }

        else if(dstValue.type() == typeid(MLimitFloat))
        {
            float v = boost::lexical_cast<float>(valueString);
            MLimitFloat limitFloat = boost::any_cast<MLimitFloat>(dstValue);
            if(v >= limitFloat.mMin && v<= limitFloat.mMax)
                limitFloat.mValue = v;
            dstValue = limitFloat;
        }
        else if(dstValue.type() == typeid(bool))
        {
            //bool v = boost::lexical_cast<bool>(valueString);
            if(valueString == "true" || valueString == "1" || valueString == "on" || valueString == "yes")
                dstValue = true;
            else if(valueString == "false" || valueString == "0"  || valueString == "off"  || valueString == "no")
                dstValue = false;
            else
            {
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::convertMStringToValue ,input syntax error."));
                    return false;
            }
            //dstValue = v;
        }
        else if(dstValue.type() == typeid(MString))
        {
            dstValue = valueStr;
        }
        else if(dstValue.type() == typeid(MEnumList))
        {
            // FIXME: need to be refactored.
            MString valueString = MString::fromUtf8(trim(valueStr.toUtf8().constData()).c_str());
            MEnumList enumList = boost::any_cast<MEnumList>(dstValue);
            // if found
            if(std::find(enumList.mStringList.begin(),enumList.mStringList.end(),valueString) != enumList.mStringList.end())
            {
                // change the select string;
                enumList.mStrSelected = valueString;
                dstValue = enumList;
            }
            else
            {
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error,not not found the string in the enumList.")+valueString);
                return false;
            }
        }
        else if(dstValue.type() == typeid(MVector2))
        {

            MVector2 vec;
            vector<string> split_str_list ;
            split_str_list = tokenize(valueString," ,", true, false, "");

            if(split_str_list.size()==2)
            {
                vec.x = boost::lexical_cast<MReal>(split_str_list[0]);
                vec.y = boost::lexical_cast<MReal>(split_str_list[1]);
                dstValue = vec;
            }
            else
            {
                //dstValue = MVector2::ZERO;
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error, you should input 2 MVector2 value"));
                    return false;
            }
        }
        else if(dstValue.type() == typeid(MVector3))
        {

            MVector3 vec;
            vector<string> split_str_list ;
            split_str_list = tokenize(valueString," ,", true, false, "");

            if(split_str_list.size()==3)
            {
                vec.x = boost::lexical_cast<MReal>(split_str_list[0]);
                vec.y = boost::lexical_cast<MReal>(split_str_list[1]);
                vec.z = boost::lexical_cast<MReal>(split_str_list[2]);
                dstValue = vec;
            }
            else
            {
                //dstValue = MVector3::ZERO;
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error, you should input 3 MVector3 value"));
                    return false;
            }
        }
        else if(dstValue.type() == typeid(MVector4))
        {

            MVector4 vec;
            vector<string> split_str_list ;
            split_str_list = tokenize(valueString," ,", true, false, "");

            if(split_str_list.size()==4)
            {
                vec.x = boost::lexical_cast<MReal>(split_str_list[0]);
                vec.y = boost::lexical_cast<MReal>(split_str_list[1]);
                vec.z = boost::lexical_cast<MReal>(split_str_list[2]);
                vec.w = boost::lexical_cast<MReal>(split_str_list[3]);
                dstValue = vec;
            }
            else
            {
                //dstValue = MVector4::ZERO;
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error, you should input 4 MVector4 value"));
                    return false;
            }
        }
        else if(dstValue.type() == typeid(MMatrix3))
        {

            MReal m[9];
            vector<string> split_str_list ;
            split_str_list = tokenize(valueString," ,", true, false, "");

            if(split_str_list.size()==9)
            {
                m[0] = boost::lexical_cast<MReal>(split_str_list[0]);
                m[1] = boost::lexical_cast<MReal>(split_str_list[1]);
                m[2] = boost::lexical_cast<MReal>(split_str_list[2]);
                m[3] = boost::lexical_cast<MReal>(split_str_list[3]);
                m[4] = boost::lexical_cast<MReal>(split_str_list[4]);
                m[5] = boost::lexical_cast<MReal>(split_str_list[5]);
                m[6] = boost::lexical_cast<MReal>(split_str_list[6]);
                m[7] = boost::lexical_cast<MReal>(split_str_list[7]);
                m[8] = boost::lexical_cast<MReal>(split_str_list[8]);

                MMatrix3 mat(m[0],m[1],m[2],m[3],m[4],m[5],m[6],m[7],m[8]);
                dstValue = mat;
            }
            else
            {
                //dstValue = MMatrix3::IDENTITY;
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error, you should input 3x3 matrix value"));
                    return false;
            }
        }
        else if(dstValue.type() == typeid(MVector4))
        {

            MReal m[16];
            vector<string> split_str_list ;
            split_str_list = tokenize(valueString," ,", true, false, "");

            if(split_str_list.size()==16)
            {
                m[0] = boost::lexical_cast<MReal>(split_str_list[0]);
                m[1] = boost::lexical_cast<MReal>(split_str_list[1]);
                m[2] = boost::lexical_cast<MReal>(split_str_list[2]);
                m[3] = boost::lexical_cast<MReal>(split_str_list[3]);
                m[4] = boost::lexical_cast<MReal>(split_str_list[4]);
                m[5] = boost::lexical_cast<MReal>(split_str_list[5]);
                m[6] = boost::lexical_cast<MReal>(split_str_list[6]);
                m[7] = boost::lexical_cast<MReal>(split_str_list[7]);
                m[8] = boost::lexical_cast<MReal>(split_str_list[8]);
                m[9] = boost::lexical_cast<MReal>(split_str_list[9]);
                m[10] = boost::lexical_cast<MReal>(split_str_list[10]);
                m[11] = boost::lexical_cast<MReal>(split_str_list[11]);
                m[12] = boost::lexical_cast<MReal>(split_str_list[12]);
                m[13] = boost::lexical_cast<MReal>(split_str_list[13]);
                m[14] = boost::lexical_cast<MReal>(split_str_list[14]);
                m[15] = boost::lexical_cast<MReal>(split_str_list[15]);


                MMatrix4 mat(m[0],m[1],m[2],m[3],m[4],m[5],m[6],m[7],m[8],m[9],m[10],m[11],m[12],m[13],m[14],m[15]);
                dstValue = mat;
            }
            else
            {
                //dstValue = MMatrix4::IDENTITY;
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error, you should input 4x4 matrix value"));
                    return false;
            }
        }
        else if(dstValue.type() == typeid(MQuaternion))
        {

            MQuaternion quat;
            vector<string> split_str_list ;
            split_str_list = tokenize(valueString," ,", true, false, "");

            if(split_str_list.size()==4)
            {
                quat.x = boost::lexical_cast<MReal>(split_str_list[0]);
                quat.y = boost::lexical_cast<MReal>(split_str_list[1]);
                quat.z = boost::lexical_cast<MReal>(split_str_list[2]);
                quat.w = boost::lexical_cast<MReal>(split_str_list[3]);
                dstValue = quat;
            }
            else
            {
                //dstValue = MVector4::ZERO;
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error, you should input 4 MVector4 value"));
                    return false;
            }
        }
        //MComboAttr
        else if(dstValue.type() == typeid(MComboAttr))
        {
            //string valueString = valueStr.toUtf8().constData());
            vector<string> split_str_list ;
            split_str_list = bracketSplit(trim(valueStr.toUtf8().constData()), ('{'), ('}'));
            MComboAttr comboAttr = getValue<MComboAttr>();
            if(comboAttr.mValueList.size() != split_str_list.size())
            {
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error, params number for MComboAttr not macth"));
                return false;
            }
            std::map<string, boost::any>::iterator it;
            it = comboAttr.mValueList.begin();
            for(size_t i=0; i < split_str_list.size(); i++)
            {
                if(!_setValueByString(it->second, MString::fromUtf8(split_str_list[i].c_str())))
                {
                    MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error, on MComboAttr"));
                    return false;
                }
                it++;
            }

            dstValue = comboAttr;
        }
        else if(dstValue.type() == typeid(MColor))
        {
            MColor bgColor;
            vector<string> split_str_list ;
            split_str_list = tokenize(valueString," ,", true, false, "");

            if(split_str_list.size()==4)
            {
                bgColor.r = boost::lexical_cast<MReal>(split_str_list[0]);
                bgColor.g = boost::lexical_cast<MReal>(split_str_list[1]);
                bgColor.b = boost::lexical_cast<MReal>(split_str_list[2]);
                bgColor.a = boost::lexical_cast<MReal>(split_str_list[3]);
            }
            else if(split_str_list.size()==3)
            {
                bgColor.r = boost::lexical_cast<MReal>(split_str_list[0]);
                bgColor.g = boost::lexical_cast<MReal>(split_str_list[1]);
                bgColor.b = boost::lexical_cast<MReal>(split_str_list[2]);
                bgColor.a = 1.0;
            }
            else
            {
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error, you should input 3 or 4 colour value[0.0 ~ 1.0]"));
                    return false;
            }
            if(bgColor.r > 1.0 || bgColor.r < 0.0 || bgColor.g > 1.0 || bgColor.g < 0.0 || bgColor.b > 1.0 || bgColor.b < 0.0 || bgColor.a > 1.0 || bgColor.a < 0.0)
            {
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error, you should input colour value between[0.0 ~ 1.0]"));
                    return false;
            }

            dstValue = bgColor;
        }
        else
        {
            MLogManager::getSingleton().logOutput(("ERROR: MAttribute::convertMStringToValue, input attribute type not suport."));
            return false;
        }
    }
    catch (boost::bad_lexical_cast &e)
    {
        MLogManager::getSingleton().logOutput("ERROR: MAttribute::convertMStringToValue " + MString::fromUtf8(std::string(e.what()).c_str()), M_ERROR);
        return false;
    }
    return true;
}

typedef basic_string<char>::size_type S_T;
static const S_T npos = -1;
vector<string> MAttribute::tokenize(const string& src, string tok, bool trim, bool quote, string null_subst)
{
    vector<string> v;
    if( src.empty() || tok.empty() ) return v;

    S_T pre_index = 0, index = 0, len = 0;
    while( (index = src.find_first_of(tok, pre_index)) != npos )
    {
        if(quote && src.at(pre_index)=='\"')
        {
            index = src.find_first_of("\"", pre_index+1);
            if(index == npos)
                break;
            else
                v.push_back(src.substr(pre_index+1, index-pre_index-1));

            if((index+1)==src.size())
                break;
            pre_index = index+1;

            index = src.find_first_of(tok, pre_index);
            if(pre_index == index)
                pre_index = index+1;

            continue;
        }
        //--------------------------------------------------
        if( (len = index-pre_index)!=0 ) v.push_back(src.substr(pre_index, len));
        else if(trim==false)
            v.push_back(null_subst);
        pre_index = index+1;
    }
    string endstr = src.substr(pre_index);
    if( trim==false ) v.push_back( endstr.empty()?  null_subst:endstr );
    else if(!endstr.empty() ) v.push_back(endstr);
    return v;
}

vector<string> bracketSplit(const string& src, char beginChar, char endChar)
{
    vector<char> beginCharList;

    vector<string> v;
    if( src.empty() || (beginChar == endChar))
        return v;

    S_T begin_index = -1, end_index = -1, len = 0;
    for(S_T i = 0;i<src.size();i++)
    {
        if(src.at(i) == beginChar)
        {
            beginCharList.push_back(beginChar);
            if(beginCharList.size() == 1)
                begin_index = i;
        }

        if(src.at(i) == endChar)
        {
            if(beginCharList.empty())
                continue;
            beginCharList.pop_back();
            if(beginCharList.empty())
            {
                end_index = i;
                len = (end_index) - (begin_index + 1);
                if(len>0)
                v.push_back(src.substr(begin_index + 1, len));
            }
        }
    }
    return v;
}

MString MAttribute::getValuetoString() const
{
    return _getValueToString(mValue);
}

MString MAttribute::_getValueToString(const boost::any &srcValue) const
{
}

bool MAttribute::setValue(const boost::any &value)
{
}

bool MAttribute::setDefaultValue(const boost::any &value)
{
}
