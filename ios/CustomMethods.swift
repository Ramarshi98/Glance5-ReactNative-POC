//
//  CustomMethods.swift
//  AwesomeTestProject
//
//  Created by Raahil on 5/1/23.
//

import Foundation
import Glance_iOS

@objc(CustomMethods) class CustomMethods: NSObject {
  @objc static func requiresMainQueueSetup() -> Bool { return true }
  @objc public func simpleMethod() { /* do something */ }
  @objc public func startVisitorSession(
    _ callback: RCTResponseSenderBlock
  ) {
//    callback(["Set Glance Server here, then start visitor session, then mask keyboard"])
    // Configure Glance Visitor SDK
    GlanceVisitor.initVisitor(21548, token: "", name: "", email: "", phone: "")
    GlanceVisitor.startSession()
  }
  @objc public func startPresence(
    _ groupId: String,
    callback: RCTResponseSenderBlock
  ) {
    callback(["startPresence('\(groupId)')"])
  }
//  @objc public func throwError() throws {
//    throw createError(message: "CustomMethods.throwError()")
//  }
  @objc public func endSession(
    _ callback: RCTResponseSenderBlock
  ) {
    callback(["endSession goes here"])
  }
  @objc public func resolvePromise(
    _ resolve: RCTPromiseResolveBlock,
    rejecter reject: RCTPromiseRejectBlock
  ) -> Void {
    resolve("CustomMethods.resolvePromise()")
  }
  @objc public func rejectPromise(
    _ resolve: RCTPromiseResolveBlock,
    rejecter reject: RCTPromiseRejectBlock
  ) -> Void {
    reject("0", "CustomMethods.rejectPromise()", nil)
  }
}
