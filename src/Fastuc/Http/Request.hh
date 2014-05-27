<?hh // strict
namespace Fastuc\Http;

class Request
{
	static function createFromCurrentRequest()
	{
		$request = new Request;
		$request->setMethod( $_SERVER['REQUEST_METHOD'] );
		return $request;
	}

	/**
	 * @var string
	 */
	private string $url;	

	/**
	 * @var string
	 */
	private string $method;

	/**
	 * @var string
	 */
	private string $userString;

	/**
	 * @var array
	 */
	private array $headers;

	private \Fastuc\Input\Server $server;

	public function __construct()
	{
		$this->headers = array();

		$this->server = new \Fastuc\Input\Server;
	}

	/**
	 * @return string
	 */
	public function getMethod() : string
	{
		return $this->method;
	}

	/**
	 * @param string $method
	 */
	public function setMethod( string $method ) : void
	{
		$this->method = $method;
	}

	/**
	 * @param bool $asArray
	 * @return string|array
	 */
	public function getAcceptLanguage( bool $asArray = false ) : mixed
	{
		$acceptLanguageHeader = $this->server->getParam( 'HTTP_ACCEPT_LANGUAGE' );
		return $asArray ?
			array_filter( explode( ',', $acceptLanguageHeader ) ) :
			$acceptLanguageHeader;
	}

	/**
	 * @return string
	 */
	public function getUserAgent() : string
	{
		return $this->userAgent;
	}

	/**
	 * @param string $userAgent
	 */
	public function setUserAgent( string $userAgent ) : void
	{
		$this->userAgent = $userAgent;
	}

	public function addHeader( string $header ) : void
	{
		$this->headers[] = $header;
	}

	/**
	 * @return array
	 */
	public function getHeaders() : array
	{
		return $this->headers;
	}

	/**
	 * @param string $url
	 */
	public function setUrl( string $url ) : void
	{
		$this->url = $url;
	}

	/**
	 * @return string
	 */
	public function getUrl() : string
	{
		return $this->url;
	}
}

