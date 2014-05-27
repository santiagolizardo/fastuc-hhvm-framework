<?hh // strict
namespace Fastuc\Http;

class Client
{
	/**
	 * @var array
	 */
	private static array $httpRequestListeners = array();

	public static function AddHttpRequestListener( RequestListener $httpRequestListener )
	{
		self::$httpRequestListeners[] = $httpRequestListener;
	}

	/**
	 * @var integer
	 */
	private int $timeout;

	/**
	 */
	public function __construct()
	{
		$this->timeout = 10;
	}

	/**
	 * @param \Fastuc\Http\Request
	 * @return \Fastuc\Http\Response
	 */
	public function send( \Fastuc\Http\Request $request ) : void
	{
		$response = new \Fastuc\Http\Response;

		foreach( self::$httpRequestListeners as $httpRequestListener )
		{
			$httpRequestListener->onHttpRequest( $request->getUrl() );
		}

		$ch = curl_init();

		curl_setopt( $ch, CURLOPT_URL, $request->getUrl() );
		curl_setopt( $ch, CURLOPT_HEADER, false );
		curl_setopt( $ch, CURLOPT_RETURNTRANSFER, true );
		curl_setopt( $ch, CURLOPT_REFERER, null );
		curl_setopt( $ch, CURLOPT_FOLLOWLOCATION, true );
		curl_setopt( $ch, CURLOPT_HTTPHEADER, $request->getHeaders() );

		$isPostRequest = ( 'POST' === $request->getMethod() );
		curl_setopt( $ch, CURLOPT_POST, $isPostRequest );
		if( $isPostRequest && !empty( $request->getParameters() ) )
		{
			curl_setopt( $ch, CURLOPT_POSTFIELDS, $request->getParameters() );
		}

		curl_setopt( $ch, CURLOPT_USERAGENT, $request->getUserAgent() );
		curl_setopt( $ch, CURLOPT_TIMEOUT, $this->timeout );

		$response->setBody( curl_exec( $ch ) );
		$response->setStatusCode( curl_getinfo( $ch, CURLINFO_HTTP_CODE ) );

		curl_close( $ch );

		return $response;
	}
}

