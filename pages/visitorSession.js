import { Alert, Platform } from 'react-native';
import NativeModules from 'react-native';
// import AsyncStorage from '@react-native-community/async-storage';

const Glance = NativeModules.Glance

// Visitor Session statuses
export const statuses = {
  stopped: 0,
  connecting: 1,
  running: 2
};

// Presence statuses
export const presenceStatuses = {
  stopped: 0,
  connecting: 1,
  running: 2
}

export const openWebView = async () => {
  const groupID = await AsyncStorage.getItem('groupID');
  if (groupID === null || groupID.length === 0) {
    Alert.alert(
      `Unable to initialize visitor.`,
      `Please make sure you have configured your Group ID.`
    );
    return;
  }
  if (Platform.OS === 'android') {
    Glance.setGlanceGroupID(groupID);
  }

  const url = await AsyncStorage.getItem('maskingUrl');
  const querySelectors = await AsyncStorage.getItem('maskingQuerySelectors');
  const labels = await AsyncStorage.getItem('maskingLabels');
  Glance.openWebView(url, querySelectors, labels)
}

export const confirmVisitorSession = (callback) => {
  callback()
  // Alert.alert(
  //   'In-App Visual Call',
  //   `You are about to make a Visual Call to Customer Service. Your agent will be able to see your screen in this app.`,
  //   [
  //     {text: 'Cancel', style: 'cancel'},
  //     {text: 'Continue', onPress: () => callback()},
  //   ],
  //   { cancelable: false }
  // )
}

export const startVideoCall = async (camera) => {
  const groupID = await AsyncStorage.getItem('groupID');
  const visitorID = await AsyncStorage.getItem('visitorID');
  // TODO: add glancevoice related logic here
  if (groupID === null || groupID.length === 0) {
    Alert.alert(
      `Unable to start your visitor session.`,
      `Please make sure you have configured your Group ID.`
    );
    return;
  }

  if (Platform.OS === 'android') {
    Glance.setGlanceGroupID(groupID);
  }

  const glanceService = await AsyncStorage.getItem('glanceService');
  if ((glanceService != null) && (glanceService != '')){
    Glance.setGlanceServer(glanceService)
  }
  Glance.startVideoCall(groupID, visitorID, camera);
}

export const requestAudioPermission = async () => {
  if (Platform.OS === 'android') {
    Glance.requestAudioPermission();
  }
}

export const startVisitorSession = async () => {
//   const groupID = await AsyncStorage.getItem('groupID');
//   const visitorID = await AsyncStorage.getItem('visitorID');
//   const phoneNumber = await AsyncStorage.getItem('phoneNumber');
//   const useVoIP = await AsyncStorage.getItem('useVoIP');
//   const voipGroupID = await AsyncStorage.getItem('voipGroupID');
//   const voipApiKey = await AsyncStorage.getItem('voipApiKey');
//   const speakerphone = await AsyncStorage.getItem('speakerphone');
//   const captureMode = await AsyncStorage.getItem('captureMode');

    const groupID = 21548
    const glanceService = "www.glance.net"

  if (groupID === null || groupID.length === 0) {
    Alert.alert(
      `Unable to start your visitor session.`,
      `Please make sure you have configured your Group ID.`
    );
    return;
  }

  if (Platform.OS === 'android') {
    Glance.setGlanceGroupID(groupID);
  }

  //const glanceService = await AsyncStorage.getItem('glanceService');
  if ((glanceService != null) && (glanceService != '')){
    //Glance.setGlanceServer(glanceService)
    console.log(Glance)
  }

  const startCallOnMute = await AsyncStorage.getItem('startCallOnMute');
  const startCallOnMuteEnabled = startCallOnMute === null ? false : JSON.parse(startCallOnMute);

  const speakerphoneEnabled = speakerphone === null ? false : JSON.parse(speakerphone);
  Glance.setSpeakerphoneEnabled(speakerphoneEnabled)

  const shouldCall = useVoIP === null ? true : JSON.parse(useVoIP);
  Glance.startVisitorSession(groupID, visitorID, shouldCall, phoneNumber, voipGroupID, voipApiKey, startCallOnMuteEnabled, captureMode);
  Glance.maskKeyboard(true);
}

export const stopVisitorSession = async () => {
  Glance.endSession()
}

export const startPresence = async () => {
  const groupID = await AsyncStorage.getItem('groupID');
  const visitorID = await AsyncStorage.getItem('visitorID');

  if (groupID === null || visitorID === null) {
    Alert.alert(
      `Unable to start your visitor session.`,
      `Please make sure you have configured both your Group ID and Visitor ID in the Settings screen.`
    );
    return;
  }

  if (Platform.OS === 'android') {
    Glance.setGlanceGroupID(groupID);
  }

  const glanceService = await AsyncStorage.getItem('glanceService');
  if ((glanceService != null) && (glanceService != '')){
    Glance.setGlanceServer(glanceService)
  }

  Glance.startPresence(groupID, visitorID);
}

export const endPresence = async (onSuccess) => {
  Glance.endPresence();
  if (onSuccess) {
    onSuccess()
  }
}

export const signalFinancialPresence = (viewStr) => {
  signalPresence(`[Financial] ${viewStr} View`)
}

export const signalHealthcarePresence = (viewStr) => {
  signalPresence(`[Healthcare] ${viewStr} View`)
}

export const signalPresence = async (viewStr) => {
  Glance.signalPresence(viewStr);
}
