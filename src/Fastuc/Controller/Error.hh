<?hh // strict
namespace Fastuc\Controller;

class Error extends Base
{
	/**
	 * @param \Fastuc\Input\Http $params
	 */
	public function doGet( \Fastuc\Input\Http $params )
	{
		$errorCode = $this->getAttribute( 0 );
		$errorMessage = $this->getAttribute( 1 );

		$this->sendError( $errorCode, $errorMessage );
	}
}

