#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include "mqtt/async_client.h"

using namespace std;

const string SERVER_ADDRESS	{ "tcp://localhost:1883" };
const string CLIENT_ID		{ "paho_cpp_async_consume" };
const string TOPIC 			{ "hello" };

const int  QOS = 1;

/////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	mqtt::async_client cli(SERVER_ADDRESS, CLIENT_ID);

	auto connOpts = mqtt::connect_options_builder()
		.clean_session(false)
		.finalize();

	try {
		// Start consumer before connecting to make sure to not miss messages

		cli.start_consuming();

		// Connect to the server

		cout << "Connecting to the MQTT server..." << flush;
		auto tok = cli.connect(connOpts);

		// Getting the connect response will block waiting for the
		// connection to complete.
		auto rsp = tok->get_connect_response();

		// If there is no session present, then we need to subscribe, but if
		// there is a session, then the server remembers us and our
		// subscriptions.
		if (!rsp.is_session_present())
			cli.subscribe(TOPIC, QOS)->wait();

		cout << "OK" << endl;

		// Consume messages
		// This just exits if the client is disconnected.
		// (See some other examples for auto or manual reconnect)

		cout << "Waiting for messages on topic: '" << TOPIC << "'" << endl;

		while (true) {
			auto msg = cli.consume_message();
			if (!msg) break;
			cout << msg->get_topic() << ": " << msg->to_string() << endl;
		}

		// If we're here, the client was almost certainly disconnected.
		// But we check, just to make sure.

		if (cli.is_connected()) {
			cout << "\nShutting down and disconnecting from the MQTT server..." << flush;
			cli.unsubscribe(TOPIC)->wait();
			cli.stop_consuming();
			cli.disconnect()->wait();
			cout << "OK" << endl;
		}
		else {
			cout << "\nClient was disconnected" << endl;
		}
	}
	catch (const mqtt::exception& exc) {
		cerr << "\n  " << exc << endl;
		return 1;
	}

 	return 0;
}
