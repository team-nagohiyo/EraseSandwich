//
//  StateController.hpp
//  EraseSandwich
//
//  Created by 大原幸夫 on 2016/09/19.
//
//

#ifndef StateController_hpp
#define StateController_hpp

#include <stdio.h>

/**
 * ステートマシン用
 */
class StateBase
{
protected:
public:
    virtual int getStateID() = 0;
    
    /**
     * ステートの開始処理
     */
    virtual void begin() = 0;
    /**
     * ステートの更新処理
     */
    virtual void update(float delta) = 0;
    /**
     * ステートの終了処理
     */
    virtual void end() = 0;
};

/**
 * ステート管理
 */
template<class T>
class StateController
{
protected:
    T *m_reserve;
    T *m_before;
    T *m_current;
    
    std::vector<T*> m_StateList;
public:
    StateController()
    :m_before(nullptr)
    ,m_current(nullptr)
    ,m_reserve(nullptr)
    {
    }

    virtual ~StateController()
    {
    }
    
    /**
     * カレントステートID
     */
    int getCurrentStateId()
    {
        if(m_current)return -1;
        return m_current->getStateID();
    }
    /**
     * カレントステート
     */
    T* getCurrentState()
    {
        return m_current;
    }
    
    /**
     * ステートの追加
     */
    void addState(T * state)
    {
        if(state == nullptr)return;
        
        if(m_StateList.size() == 0) m_current = state;
        m_StateList.push_back(state);
    }
    
    /**
     * ステートの削除
     */
    T* removeState(int stateId)
    {
        auto it = m_StateList.begin();
        while( it != m_StateList.end())
        {
            if(*it == nullptr)it = m_StateList.erase(it);
                if((*it)->getStateID() == stateId)
                {
                    m_StateList.erase(it);
                    return *it;
                }
            it++;
        }
        
        return nullptr;
    }
    /**
     * ステートの削除
     */
    void removeState(T * state)
    {
        auto it = m_StateList.begin();
        while( it != m_StateList.end())
        {
            if(*it == nullptr)it = m_StateList.erase(it);
                if(*it == state)
                {
                    m_StateList.erase(it);
                    return;
                }
            it++;
        }
    }

    /**
     * ステートの変更
     */
    void chengeState(int stateId)
    {
        auto it = std::find_if(m_StateList.begin(),m_StateList.end(),
                            [=](T* state)
        {
            if(stateId == state->getStateID()) return true;
            return false;
        });
        if(it != m_StateList.end())
        {
            m_reserve = *it;
        }
    }
    
    /**
     * ステートの更新処理
     */
    void updateState(float delta)
    {
        //アップデート
        if(m_current)
        {
            m_current->update(delta);
        }
        
        //入れ替え
        if(m_reserve)
        {
            m_before = m_current;
            m_current = m_reserve;
            
            //終了処理
            m_before->end();
            
            //開始処理
            m_current->begin();
        }
        
    }
    
};


#endif /* StateController_hpp */
