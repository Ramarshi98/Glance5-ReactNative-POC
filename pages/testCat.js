import react from "react";
import { StyleSheet, Text, View, Image, ScrollView, TextInput, Button, NativeModules, TouchableOpacity } from 'react-native';
//import { startVisitorSession } from "./visitorSession";

const { CustomMethods } = NativeModules;

const testCat = () => {
    const groupID = '21548'
    const visitorID = 'testVisitorId23'

    const startSession = () => {
        CustomMethods.startVisitorSession(result => {
            alert(result)
        })
    }

    const startPresenceConnection = () => {
        CustomMethods.startPresence(groupID, result => {
            alert(result)
        })
    }

    const endCobrowse = () => {
        CustomMethods.endSession(result => {
            alert(result)
        })
    }

    return (
        <View>
            <View style={styles.container}>
                <Text>Hi Cat!</Text>
                <Image
                    source={{
                        uri: 'https://reactnative.dev/docs/assets/p_cat2.png',
                    }}
                    style={{ width: 200, height: 200 }}
                />
            </View>
            <View style={styles.formStyle}>
                <TextInput
                    style={{
                        height: 40,
                        borderColor: 'gray',
                        borderWidth: 1
                    }}
                    defaultValue="You can type in me"
                />
                <Button title='Cobrowse' onPress={startSession} />
                <Button title='Start Presence' onPress={startPresenceConnection} />
                <Button title="End Session" onPress={endCobrowse} />
            </View>
        </View>
    );
};

export default testCat;


const styles = StyleSheet.create({
    container: {
        flex: 1,
        backgroundColor: '#4287f5',
        alignItems: 'center',
        justifyContent: 'center',
        padding: 50
    },
    formStyle: {
        padding: 10
    }
});