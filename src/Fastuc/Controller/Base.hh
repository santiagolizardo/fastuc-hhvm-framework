<?hh // strict
namespace Fastuc\Controller;

use \Fastuc\ClassLoader;

/**
 * The glue between your model and view.
 */
class Base
{
	/**
	 * @var \Fastuc\ClassLoader
	 */
	protected \Fastuc\ClassLoader $classLoader;

	protected Map<string, mixed> $attributes;

	/**
	 * @object \Fastuc\Web\Redirector
	 */
	protected \Fastuc\Web\Redirector $redirector;

	/**
	 * @object \Fastuc\Http\Response
	 */
	protected \Fastuc\Http\Response $response;

	public function __construct()
	{
		$this->setClassLoader( ClassLoader::getInstance() );

		$this->attributes = new Map<string, mixed>;

		$this->setRedirector( new \Fastuc\Web\Redirector );
		$this->response = new \Fastuc\Http\Response;
	}

	/**
	 * @param \Fastuc\ClassLoader $classLoader
	 */	
	public function setClassLoader( \Fastuc\ClassLoader $classLoader ) : void
	{
		$this->classLoader = $classLoader;
	}

	/**
	 * @param \Fastuc\Web\Redirector $redirector
	 */
	public function setRedirector( \Fastuc\Web\Redirector $redirector ) : void
	{
		$this->redirector = $redirector;
	}

	/**
	 * @deprecated
	 * @see setHttpResponse
	 * @param \Fastuc\Http\Response $response
	 */
	public function setResponse( \Fastuc\Http\Response $response ) : void
	{
		$this->setHttpResponse( $response );
	}

	/**
	 * @param \Fastuc\Http\Response $httpResponse
	 */
	public function setHttpResponse( \Fastuc\Http\Response $httpResponse ) : void
	{
		$this->response = $httpResponse;
	}
	
	/**
	 * Common logic to be executed before the actual HTTP method.
	 */
	public function init() : void
	{
	}

	public function setAttributes( Map<string, mixed> $attributes ) : void
	{
		$this->attributes = $attributes;
	}

	public function getAttributes() : Map<string, mixed>
	{
		return $this->attributes;
	}

	/**
	 * @param string $name
	 * @param mixed $value
	 */
	public function setAttribute( string $name, mixed $value ) : void
	{
		$this->attributes[ $name ] = $value;
	}

	/**
	 * @param string|int $name
	 * @return mixed The parameter with the given name or null otherwise.
 	 */
	public function getAttribute( mixed $name ) : mixed
	{
		return $this->attributes->get( $name );
	}

	/**
	 * @param string|int $name
	 * @return bool
	 */
	public function issetAttribute( mixed $name ) : bool
	{
		return $this->attributes->containsKey( $name );
	}

	/**
	 * @param string $methodName
	 */
	public function beforeMethod( string $methodName ) : void
	{
	}

	/**
	 * @param string $methodName
	 */
	public function afterMethod( string $methodName ) : void
	{
	}

	/**
	 * @param string $name
	 */
	public function executeMethod( string $name ) : void
	{
		$params = new \Fastuc\Input\Http( $name );

		$methodName = 'do' . ucfirst( strtolower( $name ) );
		if( method_exists( $this, $methodName ) )
		{
			$this->$methodName( $params );
		}
		else
		{
			$this->sendError( 405 );
		}
	}

	/**
	 * This method is invoked from a GET request.
	 *
	 * @param \Fastuc\Input\Http $params GET parameters.
	 */
	public function doGet( \Fastuc\Input\Http $params ) : void
	{
		$this->sendError( 405 );
	}

	/**
	 * This method is invoked from a POST request.
	 *
	 * @param \Fastuc\Input\Http $params POST parameters.
	 */
	public function doPost( \Fastuc\Input\Http $params ) : void
	{
		$this->sendError( 405 );
	}

	/**
	 * This method is invoked from a PUT request.
	 *
	 * @param \Fastuc\Input\Http $params PUT parameters.
	 */
	public function doPut( \Fastuc\Input\Http $params ) : void
	{
		$this->sendError( 405 );
	}

	/**
	 * This method is invoked from a DELETE request.
	 *
	 * @param \Fastuc\Input\Http $params DELETE parameters.
	 */
	public function doDelete( \Fastuc\Input\Http $params ) : void
	{
		$this->sendError( 405 );
	}

	/**
	 * This method is invoked from a OPTIONS request.
	 *
	 * @param \Fastuc\Input\Http $params OPTIONS parameters.
	 */
	public function doOptions( \Fastuc\Input\Http $params ) : void
	{
		$this->sendError( 405 );
	}

	/**
	 * @param integer $errorCode
	 * @param string $errorMessage
	 */
	public function sendError( int $errorCode, string $errorMessage = null ) : void
	{
		if( empty( $errorMessage ) )
		{
			$statusCodes = $this->response->getStatusCodes();
			$errorMessage = isset( $statusCodes[ $errorCode ] ) ? $statusCodes[ $errorCode ] : null;
		}

		$this->response->setStatusCode( $errorCode );

		if( null !== $errorMessage )
		{
			$this->response->setBody( $errorMessage );
		}
		$this->response->send();
	}

	/**
	 * Returns a new instance of the class passed as first argument.
	 *
	 * @param string $className Class name. (not fully qualified)
	 * @param array $args Optional list of arguments to use during instantiation.
	 * @return object
	 */
	protected function newInstance( string $className, array $args = array() ) : mixed
	{
		return $this->classLoader->newInstance( $className, $args );
	}
}

