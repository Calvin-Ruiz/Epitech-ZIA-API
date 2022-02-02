/*
** EPITECH PROJECT, 2020
** B-YEP-500-MAR-5-1-zia-calvin.ruiz
** File description:
** IModule.hpp
*/

#ifndef IMODULE_HPP_
#define IMODULE_HPP_

class IModule {
public:
    // Receive datas from sync message flow
    // Datas can be invalidated at any time after leaving receive
    // If ROUTING_BEHAVIOR_CONDITIONNAL_ROUTING_BIT_EXT is supported and enabled and don't invoke a reply, it must return false and datas mustn't be modified
    // If ROUTING_BEHAVIOR_CONDITIONNAL_ROUTING_BIT_EXT is supported and enabled and invoke at least one reply, it must return true and datas can be modified
    // Return true if datas have been modified, false otherwise
    // If datas have not been modified by any module, it should be implicitly released by the server
    virtual bool receive(Request *datas) = 0;
    // Tell how many reply are ensured to be filled
    virtual int haveReply() {return 0;}
    // Querry a reply
    virtual Request *reply() {return {};}

    // ========== ROUTING_BEHAVIOR_SWITCH_BIT_EXT ========== //
    // Return the requestID of the next reply
    virtual int getReplyRequestID() {return -1;}

    // ========== ROUTING_BEHAVIOR_CONDITIONNAL_STAGE_BIT_EXT ========== //
    // Return the PipelineStage of the reply, and swap datas with the reply datas
    // Note that returned PipelineStage MUST be one of the dstStage of this module
    virtual PipelineStage conditionnalReply(Request *datas) {return 0;} // Yes, this is invalid, don't care while you don't support this flag

    // ========== ROUTING_BEHAVIOR_ASYNC_BIT_EXT ========== //
    // Receive datas from async message flow
    virtual void receiveAsync(Request datas) {(void) datas;}
    // Tell how many async reply are ensured to be filled
    virtual int haveAsyncReply() {return 0;}
    // Receive an async reply
    virtual Request asyncReply() {return {};}
    virtual void updateAsync() {}

    // ========== PIPELINE_RESET_EXT ========== //
    // Reinitialize the Module to reuse it for another client
    virtual void reset() {}
};

#endif /* IMODULE_HPP_ */
