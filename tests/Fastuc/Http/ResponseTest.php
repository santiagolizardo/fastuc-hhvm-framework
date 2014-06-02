<?php
namespace Fastuc\Http;

class ResponseTest extends \PHPUnit_Framework_TestCase
{
	public function testSetStatusCode()
	{
		$_SERVER['SERVER_PROTOCOL'] = 'HTTP';

		$response = $this->getMock( '\Fastuc\Http\Response', [ 'sendHeader' ] );
		$response->expects( $this->once() )
			->method( 'sendHeader' )
			->with( 'HTTP 200 OK' );
		$response->setStatusCode( 200 );
		$response->send();
	}
}

